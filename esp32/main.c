#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "m5stack_display.h"

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  19
#define PIN_NUM_CS   22

spi_device_handle_t spi;

void init_spi() {
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4*320*240
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10*1000*1000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 7,
    };
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
}

void display_char(int x, int y, char ch, uint16_t color) {
    m5stack_display_draw_char(spi, x, y, ch, color, M5STACK_DISPLAY_FONT_8X8);
}

void cmatrix_effect() {
    const int display_width = 320;
    const int display_height = 240;
    const uint16_t color = 0x07E0; // Green color in RGB565
    while (1) {
        for (int x = 0; x < display_width; x += 8) {
            for (int y = 0; y < display_height; y += 8) {
                char ch = ' ' + (esp_random() % 95); // Generate random ASCII character
                display_char(x, y, ch, color);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main() {
    init_spi();
    m5stack_display_init(spi);
    cmatrix_effect();
}
