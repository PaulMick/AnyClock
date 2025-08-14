#include <stdio.h>
#include "freertos/Task.h"
#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#include "esp_heap_caps.h"

// Board dependent
#define R1 0
#define G1 1
#define B1 2
#define R1 3
#define G1 4
#define B1 5

// Board dependent
#define A 6
#define B 7
#define C 8
#define D 9
#define LAT 10
#define OE 11
#define CLK 12

#define DISPLAY_WIDTH 64 // Horizontal pixel count of display
#define DISPLAY_HEIGHT 32 // Vertical pixel count of display
#define COLOR_DEPTH 4 // Bit depth of each of the 3 color channels
#define SCAN_LINES 2 // 1/16 -> 2 lines are scanned at a time (1/16th of the display is scanned at a time)

#define I2S_SAMPLE_RATE 2000000
#define BASE_DELAY_US 200 // Shortest delay used for I2S

// Double frame buffer
uint8_t frame_buf_in[DISPLAY_HEIGHT][DISPLAY_WIDTH][3];
uint8_t frame_buf_out[DISPLAY_HEIGHT][DISPLAY_WIDTH][3];
// Frame buffer pointers
uint8_t *frame_buf_in_ptr[DISPLAY_HEIGHT][DISPLAY_WIDTH][3] = frame_buf_in;
uint8_t *frame_buf_out_ptr[DISPLAY_HEIGHT][DISPLAY_WIDTH][3] = frame_buf_out;
// Temp pointer for swapping frame buffer pointers
uint8_t *tmp[DISPLAY_HEIGHT][DISPLAY_WIDTH][3];

// Indicator of whether the in frame buffer is completed
int in_done = 0;
int *in_done_ptr = &in_done;

// Scanning bitplane used to correctly format row pixel data into the correct format for RGB channel PWM
uint8_t *scan_bitplane_buf[COLOR_DEPTH];

// Struct containing pointers and parameters necessary to access the in frame buffer
struct DisplayHandle {
    uint8_t *frame_buf_ptr[DISPLAY_WIDTH][DISPLAY_HEIGHT][3];
    int width;
    int height;
    int *in_done_ptr;
};

// Initialize GPIO
void init_gpio() {
    gpio_config_t gpio_cfg = {
        .pin_bit_mask = (1ULL << A) | (1ULL << B) | (1ULL << C) | (1ULL << D) | (1ULL << LAT) | (1ULL << OE) | (1ULL << CLK),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(gpio_cfg);
    gpio_set_level(LAT, 0);
    gpio_set_level(OE, 1);
}

// Initialize I2S
void init_i2s() {
    i2s_config_t i2s_cfg = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = I2S_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_8BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 128,
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
    i2s_set_clk(I2S_NUM_0, I2S_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_8BIT, I2S_CHANNEL_MONO);
}

// TODO: Might not be needed???
void set_row(uint8_t row) {
    gpio_set_level(A, row & 0x01);
    gpio_set_level(B, row & 0x02);
    gpio_set_level(C, row & 0x04);
    gpio_set_level(D, row & 0x08);
}

// Swaps the pointers to the two frame buffers
void swap_frame_buffers() {
    *tmp = *frame_buf_0_ptr;
    *frame_buf_0_ptr = *frame_buf_1_ptr;
    *frame_buf_1_ptr = *tmp;
}

/*
Bits are added in the following manner:
If row = {{15, 15, 15}, {0, 0, 0}, {10, 5, 1}}
which in binary is {{0b00001111, 0b00001111, 0b00001111}, {0b00000000, 0b0000000, 0b00000000}, {0b00001010, 0b00000101, 0b00000001}}
because even though the color channel depth can be lower than 8 (I'm using 4 for speed) they are stored as uint8 and the first 4 bits are disregarded

This is then read in as {{0b00000111, 0b00000000, 0b00000100}, {0b00000111, 0b00000000, 0b00000010}, {0b00000111, 0b00000000, 0b00000100}, {0b00000111, 0b00000000, 0b00000011}}
*/
void prep_bitplanes(uint8_t row) {
    // Add color channels in by bit depth
    for (int bit_depth = 0; bit_depth < COLOR_DEPTH; bit_depth ++) {
        uint8_t *buf = scan_bitplane_buf[bit_depth];
        // Add the bit at the current bit depth from every pixel in the row to the bitplane
        for (int col = 0; col < DISPLAY_WIDTH; col ++) {
            uint8_t r = *frame_buf_out_ptr[row][col][0];
            uint8_t g = *frame_buf_out_ptr[row][col][1];
            uint8_t b = *frame_buf_out_ptr[row][col][2];
            uint8_t rgb_bit_slice = 0;
            rgb_bit_slice |= ((r >> (7 - bit)) & 1) << 0;
            rgb_bit_slice |= ((g >> (7 - bit)) & 1) << 1;
            rgb_bit_slice |= ((b >> (7 - bit)) & 1) << 2;
            scan_bitplane_buf[col] = rgb_bit_slice;
        }
    }
}

// Render a row to the display
void render_row(uint8_t row) {
    set_row(row);
    prep_bitplanes(row);
    for (int bit_depth = 0; bit_depth < COLOR_DEPTH; bit_depth ++) {
        uint8_t *data = scan_bitplane_buf[bit_depth];
        size_t bytes_written;
        gpio_set_level(OE, 1);
        i2s_write(I2S_NUM_0, DISPLAY_WIDTH, &bytes_written, portMAX_DELAY);
        gpio_set_level(LAT, 1);
        gpio_set_level(LAT, 0);
        gpio_set_level(OE, 0);
        ets_delay_us(BASE_DELAY_US * (1 << bit_depth));
    }
}

// Task to be run by the FreeRTOS task
void refresh_task(void *param) {
    while (1) {
        // If the in frame buffer is ready make the buffer pointer swap
        if (*in_done_ptr) {
            swap_frame_buffers()
            *in_done_ptr = 0;
        }
        // Display the out frame buffer
        for (uint8_t row = 0; row < (uint8_t) (DISPLAY_HEIGHT / SCAN_LINES); row ++) {
            render_row(row);
        }
    }
}

//
struct DisplayHandle get_display_handle() {
    struct DisplayHandle display_handle = {
        .width = DISPLAY_WIDTH,
        .height = DISPLAY_HEIGHT,
        .frame_buf_ptr = frame_buf_in_ptr,
        .in_done_ptr = in_done_ptr
    }
    return display_handle;
}

// Start the main display refresh cycle
void run_refresh() {
    init_gpio();
    init_i2s();

    for (int bit_depth = 0; bit_depth < COLOR_DEPTH; bit_depth ++) {
        scan_bitplane_buf[i] = heap_caps_malloc(DISPLAY_WIDTH, MALLOC_CAP_DMA);
        memset(scan_bitplane_buf[i], 0, DISPLAY_WIDTH);
    }

    for (int y = 0; y < DISPLAY_HEIGHT; y ++) {
        for (int x = 0; x < DISPLAY_WIDTH; x ++) {
            *frame_buf_in[y][x][0] = x;
            *frame_buf_in[y][x][1] = y;
            *frame_buf_in[y][x][2] = x + y;
        }
    }

    for (int y = 0; y < DISPLAY_HEIGHT; y ++) {
        for (int x = 0; x < DISPLAY_WIDTH; x ++) {
            *frame_buf_out[y][x][0] = x;
            *frame_buf_out[y][x][1] = y;
            *frame_buf_out[y][x][2] = x + y;
        }
    }

    xTaskCreatePinnedToCore(refresh_task, "Refresh Task", 4096, NULL, 1, NULL, 0);
}