#include "encoder.h"

void dummy(void) {}

void (*function_ccw)(void) = dummy;
void (*function_cw)(void) = dummy;
void (*function_key_down)(void) = dummy;

struct Encoder encoder;

void encoder_set_on_ccw_listener(void (*function)(void)) {
    function_ccw = function;
}

void encoder_set_on_cw_listener(void (*function)(void)) {
    function_cw = function;
}

void encoder_set_on_key_down_listener(void (*function)(void)) {
    function_key_down = function;
}

void encoder_init(void) {
    encoder.key_ms = 0;
    encoder.count = 0;
    encoder.ccw = 1;
    IT1 = 1;         // 使能INT1下降沿中断
    EX1 = 1;         // 使能INT1中断
    IT0 = 1;         // 使能INT0下降沿中断
    EX0 = 1;         // 使能INT0中断
    INTCLKO |= 0x10; // 使能INT2中断
}

void INT0_ISR_Handler(void) interrupt INT0_VECTOR {
    if (P33) {
        encoder.count++;
        encoder.ccw = 1;
        function_ccw();
        // uart_send(encoder.count);
    }
}

void INT1_ISR_Handler(void) interrupt INT1_VECTOR {
    if (P32) {
        encoder.count--;
        encoder.ccw = 0;
        function_cw();
        // uart_send(encoder.count);
    }
}

void INT2_ISR_Handler(void) interrupt INT2_VECTOR {
    // uart_send(0x11);
    function_key_down();
}