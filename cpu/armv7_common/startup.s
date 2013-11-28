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

.section .startup
.func _startup
.global _startup
_startup: b    reset
    ldr pc, _undefined_instruction
    ldr pc, _software_interrupt
    ldr pc, _prefetch_abort
    ldr pc, _data_abort
    ldr pc, _not_used
    ldr pc, _irq
    ldr pc, _fiq

_undefined_instruction: .word UNDEF_Routine
_software_interrupt: .word ctx_switch
_prefetch_abort: .word PABT_Routine
_data_abort: .word DABT_Routine
_not_used: .word not_used
_irq: .word arm_irq_handler
_fiq: .word fiq
_pad: .word 0xdeadbeef

/*
 * reset code
 */
reset:
    /* FIQ mode stack */
    msr CPSR_c, #(FIQ_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr sp, =__fiq_stack_top__  /* set the FIQ stack pointer */

    /* IRQ mode stack */
    msr CPSR_c, #(IRQ_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr sp, =__irq_stack_top__  /* set the IRQ stack pointer */

    /* Supervisor mode stack */
    msr CPSR_c, #(SVC_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr sp, =__svc_stack_top__  /* set the SVC stack pointer */

    /* Undefined mode stack */
    msr CPSR_c, #(UND_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr  sp, =__und_stack_top__  /* set the UND stack pointer */

    /* Abort mode stack */
    msr CPSR_c, #(ABT_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr sp, =__abt_stack_top__  /* set the ABT stack pointer */

    /* System mode stack */
    msr CPSR_c, #(SYS_MODE | IRQ_DISABLE | FIQ_DISABLE)
    ldr sp, =__sys_stack_top__  /* set the SYS stack pointer */
    
    /* disable FIQ and IRQ, set cpu to SYS mode (not if in HYP mode) */
    mrs     r0, cpsr
    and     r1, r0, #CPSR_MODE_BITS /* mask mode bits */
    teq     r1, #0x1a               /* test if HYP mode */
    bicne   r0, r0, #CPSR_MODE_BITS /* clear all mode bits */
    orrne   r0, r0, #SYS_MODE       /* set SYS mode */
    orr     r0, r0, #0xc0           /* disable FIQ and IRQ */
    msr     cpsr, r0
    
    mrc     p15, 0, r1, c0, c0, 5   /* Read Multiprocessor Affinity Register */
    and     r1, r1, #0x3            /* Extract CPU ID bits */
    cmp     r1, #0
    beq     initialize              /* if we’re on CPU0 goto the start */

wait_loop:
    @b wait_loop

initialize:
    bl      cpu_init_cp15
    bl      bootloader

    b       kernel_init

cpu_init_cp15:
    /* Invalidate L1 I/D-Cache */
    eor     r0, r0, r0              /* prepare r0 */
    mcr     p15, 0, r0, c8, c7, 0   /* invalidate TLBs */
    mcr     p15, 0, r0, c7, c5, 0   /* invalidate I-Cache */
    mcr     p15, 0, r0, c7, c5, 6   /* invalidate BP array */
    @mcr     p15, 0, r0, c7, c10, 4  /* DSP */
    @mcr     p15, 0, r0, c7, c5, 4   /* ISB */

    /* Disable MMU and chaches */
    mrc     p15, 0, r0, c1, c0, 0   /* get it */
    bic     r0, r0, #0x00002000     /* clear bit 13 */
    bic     r0, r0, #0x00000007     /* clear bits 2:0 */
    orr     r0, r0, #0x00000800     /* set bit 11 Align*/
    orr     r0, r0, #0x00000002     /* set bit 1 BTB*/
    orr     r0, r0, #0x00001000     /* set bit 12 I-Cache */
    mcr     p15, 0, r0, c1, c0, 0   /* restore it */

    /*
     * TODO: 
     * Handle ARM errata 716044, 742230, 743622, 751472 here if needed.
     */
  #   @ Disable MMU 
#     mrc p15, 0, r1, c1, c0, 0   @ Read Control Register configuration data
#     bic r1, r1, #0x1
#     mcr p15, 0, r1, c1, c0, 0   @ Write Control Register configuration data
#  
# 
#     @ Disable L1 Caches
#     mrc p15, 0, r1, c1, c0, 0   @ Read Control Register configuration data 
#     bic r1, r1, #(0x1 << 12)    @ Disable I Cache
#     bic r1, r1, #(0x1 << 2)     @ Disable D Cache
#     mcr p15, 0, r1, c1, c0, 0   @ Write Control Register configuration data
# 
#     @ Invalidate L1 Caches
#     @ Invalidate Instruction cache 
#     mov r1, #0
#     mcr p15, 0, r1, c7, c5, 0
# 
#     @ Invalidate Data cache
#     @ to make the code general purpose, we calculate the 
#     @ cache size first and loop through each set + way
#     mrc p15, 1, r0, c0, c0, 0   @ Read Cache Size ID
#     mov r3, #0xff
#     add r3, r3, #0x100
#     and r0, r3, r0, LSR #13     @ r0 = no. of sets - 1
#     mov r1, #0                  @ r1 = way counter way_loop
# way_loop:
#     mov r3, #0                  @ r3 = set counter set_loop
# set_loop:
#     mov r2, r1, LSL #30 
#     orr r2, r3, LSL #5          @ r2 = set/way cache operation format
#     mcr p15, 0, r2, c7, c6, 2   @ Invalidate line described by r2
#     add r3, r3, #1              @ Increment set counter
#     cmp r0, r3                  @ Last set reached yet?
#     bne set_loop                @ if not, iterate set_loop
#     add r1, r1, #1              @ else, next
#     cmp r1, #4                  @ Last way reached yet?
#     bne way_loop                @ if not, iterate way_loop

    mov     pc, lr      /* return */


c_runtime_cpu_setup:
    /* Invalidate I-Cache */
    mcr     p15, 0, r0, c7, c5, 0   /* invalidate I-cache */
    @mcr     p15, 0, r0, c7, c10, 4  /* DSB */
    @mcr     p15, 0, r0, c7, c5, 4   /* ISB */

@    /* set vector address in cp15 VBAR reg */
@    ldr     r0 ,=_start
@    mcr     p15, 0, r0, c12, c0, 0  /* set VBAR */

    bx      lr                      /* back to caller */


/*
 * And now for something completly different.
 * exception handlers
 */
    .align 5

not_used:

    .align 5
    
fiq:
    
    .align 5
