/*
 * ktt20_uart.c - ktt20 UART driver
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 */

#include <stdint.h>
#include "ktt20_uart.h"

void ktt20_uart_init(uint8_t uart_number, uint32_t baudrate) {
    uint32_t uart_base = 0;
    
    switch (uart_number) {
        case 0:
            uart_base = UART0_BASE;
            break;
        case 1:
            uart_base = UART1_BASE;
            break;
        case 2:
            uart_base = UART2_BASE;
            break;
        case 3:
            uart_base = UART3_BASE;
            break;
    }
    
    /* disable uart and program baudrate */
    *UART_IIR_FCR(uart_base) = 0;
    *UART_IER_DLAB(uart_base) = 0;
    *UART_LCR(uart_base) = UART_LCR_DIVISOR_LATCH_ACCESS_FLAG;
    *UART_THR_DLAB(uart_base) = ((UART_CLK_HZ / 16) / baudrate);
    *UART_LCR(uart_base) = 0;
    *UART_IER_DLAB(uart_base) = 0;
    
    /* set UART mode */
    *UART_IIR_FCR(uart_base) = UART_FCR_RESET_TX_FLAG | UART_FCR_RESET_RX_FLAG;
    *UART_LCR(uart_base) = ( 3 & UART_LCR_WORD_LENGTH_SELECT_MASK) /* 8 bits, without parity, 1 stop bit */
                            | UART_FCR_RESET_TX_EMPTY_INT_FLAG;
    
    if (uart_number != 0) {
        *UART_MCR(uart_base) = UART_MCR_RTS_FLAG | UART_MCR_OUT2_FLAG | UART_MCR_LOOP_FLAG;
    } else {
        *UART_MCR(uart_base) = UART_MCR_RTS_FLAG | UART_MCR_OUT2_FLAG;
    }
    
    *UART_MSR(uart_base) = 0;
    *UART_SPR(uart_base) = 0;
    *UART_IRDA_CSR(uart_base) = 0;
    *UART_ASR(uart_base) = 0;
    
    // enable interrupts here
    
    *UART_IIR_FCR(uart_base) = UART_FCR_TX_RX_ENABLE_FLAG;
}

void ktt20_uart1_putc(uint8_t c) {
    while ((*UART_LSR(UART1_BASE) & UART_LSR_TXE_FLAG) == 0) {
        /* wait */
    }
    *UART_THR_DLAB(UART1_BASE) = c;
}

uint8_t ktt20_uart1_getc(void) {
    while ((*UART_LSR(UART1_BASE) & UART_LSR_RXDR_FLAG) != 0) {
        /* wait */
    }
    return *UART_THR_DLAB(UART1_BASE);
}

void ktt20_uart2_putc(uint8_t c) {
    while ((*UART_LSR(UART2_BASE) & UART_LSR_TXE_FLAG) == 0) {
        /* wait */
    }
    *UART_THR_DLAB(UART2_BASE) = c;
}

uint8_t ktt20_uart2_getc(void) {
    while ((*UART_LSR(UART2_BASE) & UART_LSR_RXDR_FLAG) != 0) {
        /* wait */
    }
    return *UART_THR_DLAB(UART2_BASE);
}

void ktt20_uart3_putc(uint8_t c) {
    while ((*UART_LSR(UART3_BASE) & UART_LSR_TXE_FLAG) == 0) {
        /* wait */
    }
    *UART_THR_DLAB(UART3_BASE) = c;
}

uint8_t ktt20_uart3_getc(void) {
    while ((*UART_LSR(UART3_BASE) & UART_LSR_RXDR_FLAG) != 0) {
        /* wait */
    }
    return *UART_THR_DLAB(UART3_BASE);
}

static inline uint32_t uart0_puts(uint8_t *astring, uint32_t length)
{
    uint32_t i = 0;

    for (; i < length; i++) {
        ktt20_uart3_putc(astring[i]);
    }

    return i;
}

void stdio_flush(void)
{
    
    while ((*UART_LSR(UART3_BASE) & UART_LSR_RXDR_FLAG) == 0) {
        (void)*UART_THR_DLAB(UART3_BASE);
    }
    while ((*UART_LSR(UART3_BASE) & UART_LSR_TXE_FLAG) != 0) {
        /* wait */
    }
}


int fw_puts(char *astring, int length)
{
    return uart0_puts((uint8_t *) astring, (uint32_t) length);
}

int bl_uart_init(void)
{
    ktt20_uart_init(3, 115200);
    return 1;
}
