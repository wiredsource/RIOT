/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     board_agilefox
 * @{
 *
 * @file        at86rf231_spi2.c
 * @brief       Board specific implementations for the at86rf231 SPI interface
 *
 * @author      Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * @}
 */


#include "cpu.h"
#include "spi.h"
#include "periph_conf.h"

/*
SPI2
  SCLK : PB13
  MISO : PB14
  MOSI : PB15
  CS : PA1

GPIO
  IRQ0 : PC2 : Frame buff empty indicator
  DIG2 : TIM3_CH4 : RX Frame Time stamping TODO : NOT USED, TIM3 is used as general timer.
  Reset : PC1 : active low, enable chip
  SLEEP : PA0 : control sleep, tx & rx state
*/

uint8_t at86rf231_spi_transfer_byte(uint8_t byte)
{
    char ret;
    spi_transfer_byte(SPI_0, byte, &ret);
    return ret;
}

void at86rf231_spi_transfer(const uint8_t *data_out, uint8_t *data_in, uint16_t length)
{
    spi_transfer_bytes(SPI_0, (char*)data_out, (char*)data_in, length);
}
