
#ifndef __SYSTEM_CONFIG__
#define __SYSTEM_CONFIG__

#include "stc8h.h"

#define uint8_t unsigned char
#define int8_t char
#define uint16_t unsigned int
#define int16_t int
#define uint32_t unsigned long
#define int32_t long


#define FOSC 42000000UL
#define BRT (65536 - FOSC / 115200 / 4)

void gpio_init(void);

#endif
