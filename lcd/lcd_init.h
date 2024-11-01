#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "../system_config.h"

#define USE_HORIZONTAL 0 // 设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 240
#define LCD_H 320

#else

#define LCD_W 320
#define LCD_H 240

#endif

sbit BLK = P1 ^ 6; // 接转接板的BLK
sbit RES = P0 ^ 0; // 接转接板的RES
sbit CS = P3 ^ 5;  // 接转接板的CS
sbit DC = P1 ^ 7;  // 接转接板的RS
sbit W_R = P3 ^ 7; // 接转接板的WR
sbit R_D = P5 ^ 4; // 接转接板的RD

#define DATAOUT P2 // P00~P07

#define LCD_BLK_Set() BLK = 1;
#define LCD_RES_Set() RES = 1;
#define LCD_CS_Set() CS = 1;
#define LCD_DC_Set() DC = 1;
#define LCD_WR_Set() W_R = 1;
#define LCD_RD_Set() R_D = 1;

#define LCD_BLK_Clr() BLK = 0;
#define LCD_RES_Clr() RES = 0;
#define LCD_CS_Clr() CS = 0;
#define LCD_DC_Clr() DC = 0;
#define LCD_WR_Clr() W_R = 0;
#define LCD_RD_Clr() R_D = 0;

void delay_ms(unsigned int ms); // 不准确延时函数
void LCD_Writ_Bus(uint8_t dat); // 模拟SPI时序
void LCD_WR_DATA8(uint8_t dat); // 写入一个字节
void LCD_WR_DATA(uint16_t dat); // 写入两个字节
void LCD_WR_REG(uint8_t dat);   // 写入一个指令
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // 设置坐标函数
void LCD_Init(void);               // LCD初始化
#endif
