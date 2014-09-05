/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     board_iot-lab_M3
 * @{
 *
 * @file        at86rf231_driver.c
 * @brief       Board specific implementations for the at86rf231 radio driver
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * @}
 */

#include <stdint.h>

#include "cpu.h"
#include "periph/gpio.h"
#include "periph/spi.h"
#include "periph_conf.h"

#include "at86rf231.h"
#include "at86rf231_arch.h"

/*
SPI1
  SCLK : PA5
  MISO : PA6
  MOSI : PA7
  CS : PA4

GPIO
  IRQ0 : PC4 : Frame buff empty indicator
  DIG2 : ? : RX Frame Time stamping XXX : NOT USED
  Reset : PC1 : active low, enable chip
  SLEEP : PA2 : control sleep, tx & rx state
*/

void at86rf231_gpio_spi_interrupts_init(void)
{
    /* set up GPIO pins */
    /* SCLK and MOSI*/
    GPIOA->CRL &= ~(0xf << (5 * 4));
    GPIOA->CRL |= (0xb << (5 * 4));
    GPIOA->CRL &= ~(0xf << (7 * 4));
    GPIOA->CRL |= (0xb << (7 * 4));
    /* MISO */
    gpio_init_in(SPI_0_MISO_GPIO, GPIO_NOPULL);

    /* SPI init */
    spi_init_master(SPI_0, SPI_CONF_FIRST_RISING, SPI_SPEED_5MHZ);

    spi_poweron(SPI_0);

    /* IRQ0 */
    gpio_init_in(SPI_0_IRQ0_GPIO, GPIO_NOPULL);
    gpio_init_int(SPI_0_IRQ0_GPIO, GPIO_NOPULL, GPIO_RISING, (gpio_cb_t)at86rf231_rx_irq, NULL);

    /* Connect EXTI4 Line to PC4 pin */
    at86rf231_enable_interrupts();

    /* CS */
    gpio_init_out(SPI_0_CS_GPIO, GPIO_NOPULL);
    /* SLEEP */
    gpio_init_out(SPI_0_SLEEP_GPIO, GPIO_NOPULL);
    /* RESET */
    gpio_init_out(SPI_0_RESET_GPIO, GPIO_NOPULL);

}
