#include "system_config.h"

void gpio_init() {
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0xf7;
    P1M1 = 0x08;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0xa0;
    P3M1 = 0x00;
    P0 = 0xff;
    P1 = 0xff;
    P2 = 0xff;
    P5M0 = 0x10;
    P5M1 = 0x00;
}
