#include "system_config.h"

#include "system_uart.h"

bit busy = 0;

void uart_init(void) {
  SCON = 0x50;
  TMOD = 0x00;
  TL1 = BRT;
  TH1 = BRT >> 8;
  TR1 = 1;
  AUXR = 0x40;
  busy = 0;
}

void uart_send(char dat) {
  while (busy)
    ;
  busy = 1;
  SBUF = dat;
}
