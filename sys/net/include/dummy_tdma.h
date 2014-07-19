#ifndef DUMMY_TDMA_H
#define DUMMY_TDMA_H

#include "radio_driver.h"
#ifdef MODULE_CC2420
#include "cc2420.h"
#elif defined MODULE_AT86RF231
#include "at86rf231.h"
#endif

void dummy_tdma_init(const ieee802154_radio_driver_t *radio);

#ifdef MODULE_CC2420
int8_t dummy_tdma_send(cc2420_packet_t *p);
#elif defined MODULE_AT86RF231
int8_t dummy_tdma_send(at86rf231_packet_t *p);
#endif

#endif /* DUMMY_TDMA_H */
