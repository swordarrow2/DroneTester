#include "pwm.h"

void pwm_init(void) {
  P_SW2 = 0x80;
  // PWM 4P
  PWMB_PSCR = 42;    // 42分频
  PWMA_ENO = 0x40;   // 使能PWM4P端口输出
  PWMA_CCER1 = 0x00; // 写CCMRx前必须先清零CCERx关闭通道
  PWMA_CCER2 = 0x00; // 写CCMRx前必须先清零CCERx关闭通道

  PWMA_CCMR4 = 0x68; // 设置CC4为PWM输出模式
  PWMA_CCER2 = 0x10; // 使能CC4通道
  PWMA_CCR4 = 10;    // 设置占空比时间
  PWMA_ARR = 100;    // 设置周期时间
  PWMA_BKR = 0x80;   // 使能主输出
  
  PWMA_CR1 = 0x01; // 开始计数
}

void pwm_set_servo_us(uint16_t us) { PWMB_CCR6 = (uint16_t)(us*0.97847f); }

void pwm_set_backlight_percent(uint16_t percent) { PWMA_CCR4 = percent; }
