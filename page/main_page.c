#include "main_page.h"

int8_t main_page_index = 0;
int8_t main_page_last_index = 0;
char* main_page_items[] = { "encoder", "servo", "pwm", "uart1", "uart2", "uart4" , "ws2812" };
uint8_t main_page_items_size = 7;

void main_page_update_lcd(void) {
    LCD_Fill(0, main_page_last_index * DEFAULT_FONT_SIZE, LCD_W, main_page_last_index * DEFAULT_FONT_SIZE + DEFAULT_FONT_SIZE, BACKGROUND_COLOR);
    LCD_ShowString(0, main_page_last_index * DEFAULT_FONT_SIZE, main_page_items[main_page_last_index], RED, BACKGROUND_COLOR, DEFAULT_FONT_SIZE, 0);
    LCD_Fill(0, main_page_index * DEFAULT_FONT_SIZE, LCD_W, main_page_index * DEFAULT_FONT_SIZE + DEFAULT_FONT_SIZE, FOCUS_COLOR);
    LCD_ShowString(0, main_page_index * DEFAULT_FONT_SIZE, main_page_items[main_page_index], RED, FOCUS_COLOR, DEFAULT_FONT_SIZE, 0);
}

void main_page_next(void) {
    main_page_last_index = main_page_index;
    main_page_index++;
    if (main_page_index > main_page_items_size - 1) {
        main_page_index = 0;
    }
    main_page_update_lcd();
}
void main_page_pre(void) {
    main_page_last_index = main_page_index;
    main_page_index--;
    if (main_page_index < 0) {
        main_page_index = main_page_items_size - 1;
    }
    main_page_update_lcd();
}

void main_page_enter(void) {
    switch (main_page_index) {
    case 0:
        encoder_test_init();
        break;
    case 1:
        servo_test_init();
        break;

    default:
        break;
    }
}

void main_page_init(void) {
    char i = 0;
    LCD_Fill(0, 0, LCD_W, 304, BACKGROUND_COLOR); 
    for (i = 0; i < main_page_items_size; i++) {
        LCD_ShowString(0, i * 16, main_page_items[i], RED, BACKGROUND_COLOR, 16, 0);
    }
    encoder_set_on_ccw_listener(main_page_pre);
    encoder_set_on_cw_listener(main_page_next);
    encoder_set_on_key_down_listener(main_page_enter);
    main_page_update_lcd();
}