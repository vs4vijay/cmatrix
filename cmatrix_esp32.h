#ifndef CMATRIX_ESP32_H
#define CMATRIX_ESP32_H

#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "ssd1306.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void esp32_init_display(void) {
    i2c_master_init();
    ssd1306_init();
    ssd1306_set_display_on(true);
}

void esp32_deinit_display(void) {
    ssd1306_set_display_on(false);
}

void esp32_render_frame(const char* frame) {
    ssd1306_clear_screen();
    for (int y = 0; y < OLED_HEIGHT / 8; y++) {
        for (int x = 0; x < OLED_WIDTH; x++) {
            if (frame[y * OLED_WIDTH + x] != ' ') {
                ssd1306_draw_pixel(x, y * 8, SSD1306_COLOR_WHITE);
            }
        }
    }
    ssd1306_update_screen();
}

#endif // CMATRIX_ESP32_H
