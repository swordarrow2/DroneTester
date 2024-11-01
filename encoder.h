#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "system_config.h"
#include "system_uart.h"

struct Encoder {
    uint16_t key_ms;
    char ccw;
    int count;
};

void encoder_set_on_ccw_listener(void (*function)(void));
void encoder_set_on_cw_listener(void (*function)(void));
void encoder_set_on_key_down_listener(void (*function)(void));
void encoder_init(void);

#endif