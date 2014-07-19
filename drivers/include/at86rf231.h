#ifndef AT86RF231_H_
#define AT86RF231_H_

#include <stdio.h>
#include <stdint.h>

#include "kernel_types.h"
#include "radio/types.h"
#include "radio_driver.h"

#include "ieee802154_frame.h"

#include "at86rf231/at86rf231_settings.h"

#define AT86RF231_MAX_PKT_LENGTH 127
#define AT86RF231_MAX_DATA_LENGTH 118

#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)
#define NOT_IMPL puts(__FILE__ ":" S__LINE__ " not_implemented")

/**
 *  Structure to represent a at86rf231 packet.
 */
typedef struct __attribute__((packed))
{
    /* @{ */
    uint8_t length;  			      /** < the length of the frame of the frame including fcs*/
    ieee802154_frame_t frame;   /** < the ieee802154 frame */
    int8_t rssi;                /** < the rssi value */
    uint8_t crc;                /** < 1 if crc was successfull, 0 otherwise */
    uint8_t lqi;                /** < the link quality indicator */
    /* @} */
}
at86rf231_packet_t;

extern kernel_pid_t transceiver_pid;

void at86rf231_init(kernel_pid_t tpid);
//void at86rf231_reset(void);
void at86rf231_rx(void);
void at86rf231_rx_handler(void);
void at86rf231_rx_irq(void);

int16_t at86rf231_send(at86rf231_packet_t *packet);

uint8_t at86rf231_set_channel(uint8_t channel);
uint8_t at86rf231_get_channel(void);

uint16_t at86rf231_set_pan(uint16_t pan);
uint16_t at86rf231_get_pan(void);

radio_address_t at86rf231_set_address(radio_address_t address);
radio_address_t at86rf231_get_address(void);
uint64_t at86rf231_get_address_long(void);
uint64_t at86rf231_set_address_long(uint64_t address);

void at86rf231_switch_to_rx(void);

void at86rf231_set_monitor(uint8_t mode);

enum {
    RF86RF231_MAX_TX_LENGTH = 125,
    RF86RF231_MAX_RX_LENGTH = 127,
    RF86RF231_MIN_CHANNEL = 11,
    RF86RF231_MAX_CHANNEL = 26
};

extern at86rf231_packet_t at86rf231_rx_buffer[AT86RF231_RX_BUF_SIZE];

radio_tx_status_t at86rf231_load_tx_buf(ieee802154_packet_kind_t kind,
                                        ieee802154_node_addr_t dest,
                                        bool use_long_addr,
                                        bool wants_ack,
                                        void *buf,
                                        unsigned int len);

radio_tx_status_t at86rf231_transmit_tx_buf(void);

radio_tx_status_t at86rf231_do_send(ieee802154_packet_kind_t kind,
                                    ieee802154_node_addr_t dest,
                                    bool use_long_addr,
                                    bool wants_ack,
                                    void *buf,
                                    unsigned int len);

void at86rf231_set_recv_callback(receive_802154_packet_callback_t recv_cb);

/* setter functions wrappers, to maintain compatibility with both
   ieee802154_radio_driver_t and transceiver module */

static inline void do_set_channel(unsigned int chan) {
    at86rf231_set_channel(chan);
}

static inline unsigned do_get_channel(void) {
    return (unsigned) at86rf231_get_channel();
}

static inline void do_set_monitor(bool b)
{
    at86rf231_set_monitor((uint8_t) b);
}

static inline void do_set_address(uint16_t addr) {
    at86rf231_set_address(addr);
}

static inline void do_set_long_address(uint64_t addr) {
    at86rf231_set_address_long(addr);
}

static inline void do_set_pan_id(uint16_t pan) {
    at86rf231_set_pan(pan);
}

/**
 * AT86RF231 low-level radio driver definition.
 */
extern const ieee802154_radio_driver_t at86rf231_radio_driver;

#endif
