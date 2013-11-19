/*
 * tegra2.lds - Linker script for Tegra2 devices
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 *
 * This file is part of RIOT.
 *
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)
SECTIONS
{
    /* TODO: can be increased */
    SYS_STACK_SIZE = 1024;
    IRQ_STACK_SIZE = 256;
    FIQ_STACK_SIZE = 256;
    SVC_STACK_SIZE = 256;
    ABT_STACK_SIZE = 16;
    UND_STACK_SIZE = 16;
    HEAP_SIZE = 4096;
    
    . = 0x00000000;

    . = ALIGN(4);
    .text :
    {
        *(.startup)
        *(.text*)
    }
    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);
    
    . = ALIGN(4);
    .rodata : 
    {
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
    }

    . = ALIGN(4);
    .data :
    {
        _data = . ;
        *(.data*)
    }
    _edata = .; PROVIDE (edata = .);
    
  	.stack : {
  		__stack_start__ = . ;

  		. += IRQ_STACK_SIZE;
  		. = ALIGN (4);
  		__irq_stack_top__ = . ;

  		. += FIQ_STACK_SIZE;
  		. = ALIGN (4);
  		__fiq_stack_top__ = . ;

  		. += SVC_STACK_SIZE;
  		. = ALIGN (4);
  		__svc_stack_top__ = . ;

  		. += ABT_STACK_SIZE;
  		. = ALIGN (4);
  		__abt_stack_top__ = . ;

  		. += UND_STACK_SIZE;
  		. = ALIGN (4);
  		__und_stack_top__ = . ;

  		. += SYS_STACK_SIZE;
  		. = ALIGN (4);
  		__sys_stack_top__ = . ;

  		__stack_end__ = .;
  	}

    . = ALIGN(4);
    . = .;

    . = ALIGN(4);
    .rel.dyn :
    {
        __rel_dyn_start = .;
        *(.rel*)
        __rel_dyn_end = .;
    }

    .dynsym :
    {
        __dynsym_start = .;
        *(.dynsym)
    }

    _end = .;

    .bss_start __rel_dyn_start (OVERLAY) :
    {
        KEEP(*(.__bss_start));
        __bss_start = .;
    }

    .bss __bss_start (OVERLAY) :
    {
        *(.bss*)
        . = ALIGN(4);
        __bss_end = .;
    }

    .bss_end __bss_end (OVERLAY) :
    {
        KEEP(*(.__bssend));
    }
    
    .heap : 
    {
        __heap_start__ = . ; PROVIDE(__heap_start = .);
        *(.heap);
        . += HEAP_SIZE;
        . = ALIGN (4);
        __heap_end__ = . ;  PROVIDE(__heap_end = .);
    }

    /DISCARD/ : { *(.dynstr*) }
    /DISCARD/ : { *(.dynamic*) }
    /DISCARD/ : { *(.plt*) }
    /DISCARD/ : { *(.interp*) }
    /DISCARD/ : { *(.gnu*) }
}