#include "system_config.h"

#include "./lcd/lcd.h"
#include "./lcd/lcd_init.h"
#include "./lcd/pic.h"
#include "encoder.h"
// #include "STC8H_PWM.h"
#include "./page/main_page.h"
#include "./page/servo_test.h"
#include "intrins.h"
#include "system_uart.h"

extern struct Encoder encoder;

void timer0_Init(void)		//1毫秒@42MHz
{
    AUXR |= 0x80;			//定时器时钟1T模式
    TMOD &= 0xF0;			//设置定时器模式
    TL0 = 0xF0;				//设置定时初始值
    TH0 = 0x5B;				//设置定时初始值
    TR0 = 1;				//定时器0开始计时
    ET0 = 1;
}
uint16_t ti = 0;
void show_voltage(void) {
    ADC_CONTR |= 0x43;                      //启动AD转换
    _nop_();
    _nop_();
    while (!(ADC_CONTR & 0x20));            //查询ADC完成标志
    ADC_CONTR &= ~0x20;                     //清完成标志
    //P2 = ADC_RES;                           //读取ADC结果

    LCD_ShowString(0, LCD_H - DEFAULT_FONT_SIZE, "voltage:    V", RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE, 0);
    LCD_ShowFloatNum1(64, LCD_H - DEFAULT_FONT_SIZE, ADC_RES * 3.29f / 256 * 2, 3, RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE);
// LCD_ShowIntNum(64, 304, ADC_RES, 4, RED, BACKGROUND_COLOR, 16);
}

void do_0_5_hz(void) {
    show_voltage();
}

void do_1_hz(void) {

}

void do_10_hz(void) {

}

void do_100_hz(void) {

}

void do_1000_hz(void) {

}

void Timer0_ISR_Handler(void) interrupt TMR0_VECTOR {
    ti++;
    do_1000_hz();
    if (ti % 10 == 0) {
        do_100_hz();
    }
    if (ti % 100 == 0) {
        do_10_hz();
    }
    if (ti == 1000 || ti == 2000) {
        do_1_hz();
    }
    if (ti == 2000) {
        do_0_5_hz();
        ti = 0;
    }

// if (P36 == 1) {
//     encoder.key_ms = 0;
// }
// else {
//     encoder.key_ms++;
// }
}

char focus1 = 0;
char focus2 = 0;
char filter = 0;

extern bit busy;
void UartIsr() interrupt 4 {
    if (TI) {
        TI = 0;
        busy = 0;
    }
    if (RI) {
        RI = 0;
        switch (SBUF) {

        default:
            break;
        }
    }
}
void Delay1000ms(void)	//@42MHz
{
    unsigned char data i, j, k;

    _nop_();
    i = 214;
    j = 17;
    k = 227;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

int main(void) {
    unsigned char i, j;
    float t = 0;
    int delay = 10;
    gpio_init();
    uart_init();
    LCD_Init(); // LCD初始化

    encoder_init();

    LCD_Fill(0, 0, LCD_W, LCD_H, BACKGROUND_COLOR);
    LCD_ShowString(48, 96, "welcome to :", RED, BACKGROUND_COLOR, 16, 0);
    LCD_ShowString(48, 112, "SHIT GUI!", YELLOW, BACKGROUND_COLOR, 32, 0);

        //   LCD_ShowChinese(0, 0, "中景园电子", RED, FOCUS_COLOR, 32, 0);
        //   LCD_ShowString(0, 40, "encoder:", RED, FOCUS_COLOR, 16, 0);
        //   LCD_ShowIntNum(48, 40, LCD_W, 3, RED, FOCUS_COLOR, 16);
        //   LCD_ShowString(80, 40, "LCD_H:", RED, FOCUS_COLOR, 16, 0);
        //   LCD_ShowIntNum(128, 40, LCD_H, 3, RED, FOCUS_COLOR, 16);
        //   LCD_ShowString(80, 40, "LCD_H:", RED, FOCUS_COLOR, 16, 0);
        //   LCD_ShowString(0, 70, "Increaseing Nun:", RED, FOCUS_COLOR, 16, 0);
    Delay1000ms();
    Delay1000ms();
    Delay1000ms();
    pwm_init();
    //P_SW2 |= 0x80;
    ADCTIM = 0x3f;                              //设置ADC内部时序
    //P_SW2 &= 0x7f;
    ADCCFG = 0x0f;                              //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x80;                           //使能ADC模块

    timer0_Init();
    P32 = 1;
    P33 = 1;
    ES = 1;
    EA = 1;
    //   servo_init();
    show_voltage();
    main_page_init();
    while (1) {
      //   LCD_ShowFloatNum1(128, 70, t, 8, RED, FOCUS_COLOR, 16);
        t += 1;
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 6; i++) {
              //       LCD_ShowPicture(40 * i, 120 + j * 40 - t, 40, 40, gImage_1);
            }
        }
        if (t > 255) {
            t = -255;
        }

        // UartSend(vcc >> 8);                         //输出电压值到串口
        // UartSend(vcc);
    }
}
