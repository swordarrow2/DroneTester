#include "servo_test.h"

uint16_t servo_length = 1500;
char* _servo = "servo:    ms";
char* _servo_angle = "angle:      degree";

void servo_update_lcd(void) {
    LCD_ShowString(0, 40, _servo, RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE, 0);
    LCD_ShowIntNum(sizeof(_servo) * DEFAULT_FONT_SIZE, 40, servo_length, 4, RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE);
    LCD_ShowString(0, 40 + DEFAULT_FONT_SIZE, _servo_angle, RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE, 0);
    LCD_ShowFloatNum1(sizeof(_servo_angle) * DEFAULT_FONT_SIZE, 40 + DEFAULT_FONT_SIZE, (servo_length - 500) * 9.0f / 100, 5, RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE);
}

void servo_add_length(void) {
    servo_length += 20;
    if (servo_length > 2500) {
        servo_length = 2500;
    }
    pwm_set_servo_us(servo_length);
    servo_update_lcd();
}

void servo_sub_length(void) {
    servo_length -= 20;
    if (servo_length < 500) {
        servo_length = 500;
    }
    pwm_set_servo_us(servo_length);
    servo_update_lcd();
}

void servo_reset(void) {
    servo_length = 1500;
    pwm_set_servo_us(servo_length);
    servo_update_lcd();
}

void servo_test_init(void) {
    LCD_Fill(0, 0, LCD_W, LCD_H - DEFAULT_FONT_SIZE, BACKGROUND_COLOR);
    encoder_set_on_ccw_listener(servo_sub_length);
    encoder_set_on_cw_listener(servo_add_length);
    encoder_set_on_key_down_listener(servo_reset);

    // PWM 6_3
    PWMB_PSCR = 42; // 时钟42M， 周期3000对应3ms，需要42分频     42M/333Hz=126000
                    // 126000/3000=42
    PWMB_ENO = 0x04;   // 使能PWM6端口输出
    PWMB_PS = 0x08;    // 切换至P0.1
    PWMB_CCER1 = 0x00; // 写CCMRx前必须先清零CCERx关闭通道
    PWMB_CCER2 = 0x00; // 写CCMRx前必须先清零CCERx关闭通道

    PWMB_CCMR2 = 0x68; // 设置CC2为PWM输出模式
    PWMB_CCER1 = 0x10; // 使能CC2通道
    // PWMB_CCR6 = servo_length;   // 设置占空比时间
    pwm_set_servo_us(servo_length);
    //PWMB_CCR6 =(uint16_t)(servo_length*0.97847f);
    PWMB_ARR = 3000;   // 设置周期时间
    PWMB_BKR = 0x80;   // 使能主输出

    PWMB_CR1 = 0x01; // 开始计数
    servo_update_lcd();
}
