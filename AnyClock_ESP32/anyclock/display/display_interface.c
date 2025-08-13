#include <stdio.h>
#include <freertos/Task.h>
#include <freertos/FreeRTOS.h>
#include <driver/i2s.h>
#include <driver/gpio.h>

#define R1 0
#define G1 1
#define B1 2
#define R1 3
#define G1 4
#define B1 5

#define A 6
#define B 7
#define C 8
#define D 9
#define LAT 10
#define OE 11
#define CLK 12

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define COLOR_DEPTH 4
#define SCAN_LINES 2 // 1/16 -> 2 scan lines at a time

uint8_t frame_buf[DISPLAY_HEIGHT][DISPLAY_WIDTH][3];

uint8_t *scan_bitplane_buf[COLOR_DEPTH];

void init_gpio() {
    gpio_config_t gpio_cfg = {
        .pin_bit_mask = (1ULL << A) | (1ULL << B) | (1ULL << C) | (1ULL << D) | (1ULL << LAT) | (1ULL << OE) | (1ULL << CLK),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(gpio_cfg);
}

void init_i2s() {
    i2s_config_t i2s_cfg = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = 2000000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_8BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .intr_alloc_flags = ESP_INTR_FLAP_LEVEL1
    };
    i2s_pin_config_t i2s_pin_cfg = {
        .bck_io_num = CLK,
        .ws_io_num = -1,
        .data_out_num = R1,
        .data_in_num = -1
    };
    i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &i2s_pin_cfg);
    i2s_set_clk(I2S_NUM_0, 2000000, I2S_BITS_PER_SAMPLE_8BIT, I2S_CHANNEL_MONO);
}

void set_row(uint8_t row) {
    gpio_set_level(A, row & 0x01);
    gpio_set_level(B, row & 0x02);
    gpio_set_level(C, row & 0x04);
    gpio_set_level(D, row & 0x08);
}

void prep_bitplane(uint8_t row) {

}