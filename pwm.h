#ifndef _PWM_H_
#define _PWM_H_

#include "system_config.h"

void pwm_init(void);
void pwm_set_servo_us(uint16_t);
void pwm_set_backlight_percent(uint16_t);

#endif
