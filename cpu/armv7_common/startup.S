/*
 * startup.S - Startup Code for ARM Cortex CPU-core
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT.
 *
 */

.set CPSR_MODE_BITS, 0x1f

/* Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs (program status registers) */
.set  USR_MODE, 0x10                  /* Normal User Mode                                         */
.set  FIQ_MODE, 0x11                  /* FIQ Processing Fast Interrupts Mode                      */
.set  IRQ_MODE, 0x12                  /* IRQ Processing Standard Interrupts Mode                  */
.set  SVC_MODE, 0x13                  /* Supervisor Processing Software Interrupts Mode           */
.set  ABT_MODE, 0x17                  /* Abort Processing memory Faults Mode                      */
.set  UND_MODE, 0x1B                  /* Undefined Processing Undefined Instructions Mode         */
.set  SYS_MODE, 0x1F                  /* System Running Priviledged Operating System Tasks  Mode  */

.set  IRQ_DISABLE, 0x80          /* when I bit is set, IRQ is disabled (program status registers) */
.set  FIQ_DISABLE, 0x40          /* when F bit is set, FIQ is disabled (program status registers) */

.section .vectors
.global _vectors
_vectors: 
    ldr pc, _reset_addr
    ldr pc, _undefined_instruction
    ldr pc, _software_interrupt
    ldr pc, _prefetch_abort
    ldr pc, _data_abort
    ldr pc, _not_used
    ldr pc, _irq
    ldr pc, _fiq

_reset_addr: .word reset_handler
_undefined_instruction: .word UNDEF_Routine
_software_interrupt: .word ctx_switch
_prefetch_abort: .word PABT_Routine
_data_abort: .word DABT_Routine
_not_used: .word not_used
_irq: .word arm_irq_handler
_fiq: .word fiq


/*
 * reset code
 */
reset_handler:

/*
 * Disable caches, MMU and branch prediction in case they were left 
 * enabled from an earlier run
 */
    MRC     p15, 0, r0, c1, c0, 0       @ Read CP15 System Control register
    BIC     r0, r0, #(0x1 << 12)        @ Clear I bit 12 to disable I Cache
    BIC     r0, r0, #(0x1 <<  2)        @ Clear C bit  2 to disable D Cache
    BIC     r0, r0, #0x1                @ Clear M bit  0 to disable MMU
    BIC     r0, r0, #(0x1 << 11)        @ Clear Z bit 11 to disable branch prediction
    MCR     p15, 0, r0, c1, c0, 0       @ Write value back to CP15 System Control register

/*
 * Invalidate Data and Instruction TLBs and branch predictor
 */
    MOV     r0,#0
    MCR     p15, 0, r0, c8, c7, 0      @ I-TLB and D-TLB invalidation
    MCR     p15, 0, r0, c7, c5, 6      @ BPIALL - Invalidate entire branch predictor array

/*
 * Set Vector Base Address Register (VBAR) to point to this applications vector table
 */

    LDR     r0, =.vectors
    MCR     p15, 0, r0, c12, c0, 0

/*
 * Cache Invalidation code for Cortex-A9
 */

    @ Invalidate L1 Instruction Cache
    MRC     p15, 1, r0, c0, c0, 1      @ Read Cache Level ID Register (CLIDR)
    TST     r0, #0x3                   @ Harvard Cache?
    MOV     r0, #0                     @ SBZ
    MCRNE   p15, 0, r0, c7, c5, 0      @ ICIALLU - Invalidate instruction cache and flush branch target cache

    @ Invalidate Data/Unified Caches
    MRC     p15, 1, r0, c0, c0, 1      @ Read CLIDR
    ANDS    r3, r0, #0x07000000        @ Extract coherency level
    MOV     r3, r3, LSR #23            @ Total cache levels << 1
    BEQ     Finished                   @ If 0, no need to clean

    MOV     r10, #0                    @ R10 holds current cache level << 1
Loop1:
    ADD     r2, r10, r10, LSR #1       @ R2 holds cache "Set" position 
    MOV     r1, r0, LSR r2             @ Bottom 3 bits are the Cache-type for this level
    AND     r1, r1, #7                 @ Isolate those lower 3 bits
    CMP     r1, #2
    BLT     Skip                       @ No cache or only instruction cache at this level

    MCR     p15, 2, r10, c0, c0, 0     @ Write the Cache Size selection register
    ISB                                @ ISB to sync the change to the CacheSizeID reg
    MRC     p15, 1, r1, c0, c0, 0      @ Reads current Cache Size ID register
    AND     r2, r1, #7                 @ Extract the line length field
    ADD     r2, r2, #4                 @ Add 4 for the line length offset (log2 16 bytes)
    LDR     r4, =0x3FF
    ANDS    r4, r4, r1, LSR #3         @ R4 is the max number on the way size (right aligned)
    CLZ     r5, r4                     @ R5 is the bit position of the way size increment
    LDR     r7, =0x7FFF
    ANDS    r7, r7, r1, LSR #13        @ R7 is the max number of the index size (right aligned)

Loop2:
    MOV     r9, r4                     @ R9 working copy of the max way size (right aligned)

Loop3:   
    ORR     r11, r10, r9, LSL r5       @ Factor in the Way number and cache number into R11
    ORR     r11, r11, r7, LSL r2       @ Factor in the Set number
    MCR     p15, 0, r11, c7, c6, 2     @ Invalidate by Set/Way
    SUBS    r9, r9, #1                 @ Decrement the Way number
    BGE     Loop3
    SUBS    r7, r7, #1                 @ Decrement the Set number
    BGE     Loop2
Skip:    
    ADD     r10, r10, #2               @ increment the cache number
    CMP     r3, r10
    BGT     Loop1

Finished:

/*
 * future MMU configuration and initialization should be here
 */
 
/*
 * Setup domain control register - Enable all domains to client mode
 */

    MRC     p15, 0, r0, c3, c0, 0      @ Read Domain Access Control Register
    LDR     r0, =0x55555555            @ Initialize every domain entry to b01 (client)
    MCR     p15, 0, r0, c3, c0, 0      @ Write Domain Access Control Register
    
/*
 * leave caches and MMU disabled
 */
    LDR     r12,=bootloader            @ Save this in register for possible long jump
    ldr     r11,=kernel_init
    MRC     p15, 0, r0, c1, c0, 0      @ Read CP15 System Control register
    BIC     r0, r0, #(0x1 << 12)       @ Clear I bit 12 to disable I Cache
    BIC     r0, r0, #(0x1 <<  2)       @ Clear C bit  2 to disable D Cache
    BIC     r0, r0, #0x2               @ Clear A bit  1 to disable strict alignment fault checking
    @ ORR     r0, r0, #0x1               @ Set M bit 0 to enable MMU before scatter loading
    MCR     p15, 0, r0, c1, c0, 0      @ Write CP15 System Control register
    
    bl      enable_caches
    
    bl      bootloader
    b       kernel_init


.global enable_caches
enable_caches:
/*
 * Enable caches and branch prediction
 */
    MRC     p15, 0, r0, c1, c0, 0      @ Read System Control Register
    ORR     r0, r0, #(0x1 << 12)       @ Set I bit 12 to enable I Cache
    ORR     r0, r0, #(0x1 << 2)        @ Set C bit  2 to enable D Cache
    ORR     r0, r0, #(0x1 << 11)       @ Set Z bit 11 to enable branch prediction
    MCR     p15, 0, r0, c1, c0, 0      @ Write System Control Register


/*
 * Enable L1 D-side prefetch (A9 specific)
 */
    MRC     p15, 0, r0, c1, c0, 1      @ Read Auxiliary Control Register
    ORR     r0, r0, #(0x1 << 2)        @ Set DP bit 2 to enable L1 Dside prefetch
    MCR     p15, 0, r0, c1, c0, 1      @ Write Auxiliary Control Register

    BX      lr                         @ return to caller

/*
 * And now for something completly different.
 * exception handlers
 */
    .align 5

not_used:

    .align 5
    
fiq:
    
    .align 5
