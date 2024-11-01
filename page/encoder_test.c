#include "encoder_test.h"

extern struct Encoder encoder;

void encoder_update_lcd(void) {
    LCD_ShowString(0, 40, "encoder:", RED, BACKGROUND_COLOR, 16, 0);
    LCD_ShowIntNum(64, 40, encoder.count, 4, RED, BACKGROUND_COLOR, 16);
    LCD_ShowString(0, 56, "rotation:", RED, BACKGROUND_COLOR, 16, 0);
    LCD_ShowString(72, 56, encoder.ccw == 1 ? "ccw" : " cw", RED, BACKGROUND_COLOR, 16, 0);
}

void encoder_test_add(void) {
    encoder_update_lcd();
}

void encoder_test_sub(void) {
    encoder_update_lcd();
}

void encoder_test_key(void) {
   // encoder.count = 0;
   // encoder_update_lcd();
    main_page_init();
}

void encoder_test_init(void) {
    LCD_Fill(0, 0, LCD_W, 304, BACKGROUND_COLOR);
    encoder_set_on_ccw_listener(encoder_test_sub);
    encoder_set_on_cw_listener(encoder_test_add);
    encoder_set_on_key_down_listener(encoder_test_key);
    encoder_update_lcd();
}
