/*
 * ktt20_uart.h - ktt20 UART driver
 * Copyright (C) 2013 Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 2.  See the file LICENSE for more details.
 */

#define UART0_BASE			( 0x70006000UL )			/* nVidia Tegra 2 - UART A */
#define UART1_BASE			( 0x70006040UL )			/* nVidia Tegra 2 - UART B */
#define UART2_BASE			( 0x70006200UL )			/* nVidia Tegra 2 - UART C */
#define UART3_BASE			( 0x70006300UL )			/* nVidia Tegra 2 - UART D */
#define UART4_BASE			( 0x70006400UL )			/* nVidia Tegra 2 - UART E */

#define UART_THR_DLAB(x)	( (unsigned long *)	( (x) + 0x0000UL ) )	/* Register */
#define UART_IER_DLAB(x)	( (unsigned long *)	( (x) + 0x0004UL ) )	/* Register */
#define UART_IIR_FCR(x)		( (unsigned long *)( (x) + 0x0008UL ) )		/* Register */
#define UART_LCR(x)			( (unsigned long *)	( (x) + 0x000CUL ) )	/* Register */
#define UART_MCR(x)			( (unsigned long *)( (x) + 0x0010UL ) )		/* Register */
#define UART_LSR(x)			( (unsigned long *)	( (x) + 0x0014UL ) )	/* Register */
#define UART_MSR(x)			( (unsigned long *)	( (x) + 0x0018UL ) )	/* Register */
#define UART_SPR(x)			( (unsigned long *)	( (x) + 0x001CUL ) )	/* Register */
#define UART_IRDA_CSR(x)	( (unsigned long *)( (x) + 0x0020UL ) )		/* Register */
#define UART_ASR(x)			( (unsigned long *)	( (x) + 0x003CUL ) )	/* Register */

#define UART_IER_DMA_ENABLE 			( 1 << 7 )
#define UART_IER_UNIT_ENABLE 			( 1 << 6 )
#define UART_IER_NRZ_ENABLE 			( 1 << 5 )
#define UART_IER_RX_TIMEOUT_INT_ENABLE	( 1 << 4 )
#define UART_IER_MODEM_INT_ENABLE 		( 1 << 3 )
#define UART_IER_RXLS_INT_ENABLE 		( 1 << 2 )
#define UART_IER_TXDR_INT_ENABLE 		( 1 << 1 )
#define UART_IER_RXDA_INT_ENABLE 		( 1 << 0 )

#define UART_IIR_FIFO_ENABLE_STATUS_MASK	( 3 << 6 )
#define UART_IIR_TIMEOUT_STATUS_MASK		( 1 << 3 )
#define UART_IIR_INTERRUPT_STATUS_MASK		( 3 << 1 )
#define UART_IIR_INTERRUPT_STATUS_RX_ERROR	( 3 << 1 )
#define UART_IIR_INTERRUPT_STATUS_RX_DR		( 1 << 2 )
#define UART_IIR_INTERRUPT_STATUS_TX		( 1 << 1 )
#define UART_IIR_INTERRUPT_PENDING_MASK		( 1 << 0 )

#define UART_FCR_INTERRUPT_TRIGGER_LEVEL_MASK	( 3 << 6 )
#define UART_FCR_RESET_TX_EMPTY_INT_FLAG		( 1 << 2 )
#define UART_FCR_RESET_TX_FLAG					( 1 << 2 )
#define UART_FCR_RESET_RX_FLAG					( 1 << 1 )
#define UART_FCR_TX_RX_ENABLE_FLAG				( 1 << 0 )

#define UART_LCR_DIVISOR_LATCH_ACCESS_FLAG	( 1 << 7 )
#define UART_LCR_SET_BREAK_FLAG				( 1 << 6 )
#define UART_LCR_STICKY_PARITY_FLAG			( 1 << 5 )
#define UART_LCR_EVEN_PARITY_FLAG			( 1 << 4 )
#define UART_LCR_PARITY_ENABLE_FLAG			( 1 << 3 )
#define UART_LCR_STOP_BIT_FLAG				( 1 << 2 )
#define UART_LCR_WORD_LENGTH_SELECT_MASK	( 3 << 0 )

#define UART_LSR_FIFO_ERROR_FLAG		( 1 << 7 )
#define UART_LSR_TXE_FLAG				( 1 << 6 )
#define UART_LSR_TXDR_FLAG				( 1 << 5 )
#define UART_LSR_BI_FLAG				( 1 << 4 )
#define UART_LSR_FRAME_ERROR_FLAG		( 1 << 3 )
#define UART_LSR_PARITY_ERROR_FLAG		( 1 << 2 )
#define UART_LSR_OVERRUN_ERROR_FLAG		( 1 << 1 )
#define UART_LSR_RXDR_FLAG				( 1 << 0 )

#define UART_MCR_LOOP_FLAG	( 1 << 4 )
#define UART_MCR_OUT2_FLAG	( 1 << 3 )
#define UART_MCR_OUT1_FLAG	( 1 << 2 )
#define UART_MCR_RTS_FLAG	( 1 << 1 )
#define UART_MCR_DTR_FLAG	( 1 << 0 )

#define UART_MSR_DCD_FLAG	( 1 << 7 )
#define UART_MSR_RI_FLAG	( 1 << 6 )
#define UART_MSR_DSR_FLAG	( 1 << 5 )
#define UART_MSR_CTS_FLAG	( 1 << 4 )
#define UART_MSR_DDCD_FLAG	( 1 << 3 )
#define UART_MSR_TERI_FLAG	( 1 << 2 )
#define UART_MSR_DDSR_FLAG	( 1 << 1 )
#define UART_MSR_DCTS_FLAG	( 1 << 0 )


#define UART_CLK_HZ				( 216000000UL )
#define UART0_VECTOR_ID			( 32 )

#define UART_FIFO_SIZE_BYTES	( 32UL )
#define UART1_VECTOR_ID			( 33 )
#define UART2_VECTOR_ID			( 34 )
#define UART3_VECTOR_ID			( 35 )
#define UART4_VECTOR_ID			( 36 )

#define TX_QUEUE				( 0 )
#define RX_QUEUE				( 1 )

void ktt20_uart_init(uint8_t uart_number, uint32_t baudrate);
void ktt20_uart1_putc(uint8_t c);
uint8_t ktt20_uart1_getc(void);
void ktt20_uart2_putc(uint8_t c);
uint8_t ktt20_uart2_getc(void);
void ktt20_uart3_putc(uint8_t c);
uint8_t ktt20_uart3_getc(void);
int bl_uart_init(void);
