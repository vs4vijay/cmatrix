#include "cmatrix_esp32.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

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
    for (int y = 0; y < OLED_HEIGHT; y += 8) {
        for (int x = 0; x < OLED_WIDTH; x++) {
            int index = (y / 8) * OLED_WIDTH + x;
            if (frame[index] != ' ') {
                ssd1306_draw_pixel(x, y, SSD1306_COLOR_WHITE);
            }
        }
    }
    ssd1306_update_screen();
}
