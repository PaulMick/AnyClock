#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

const char *months_full[12] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
const char *months_short[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

const char *week_days_full[7] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
const char *week_days_short[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

const uint32_t font[128];

void draw_char(uint8_t *frame_buf[DISPLAY_HEIGHT][DISPLAY_WIDTH][3], uint32_t font_char, int width, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < width; i ++) {
        for (int j = 0; j < 5; j ++) {
            if (font_char & 1 << j + 5 * i) {
                *frame_buf[y + j][i + x][0] = r;
                *frame_buf[y + j][i + x][1] = g;
                *frame_buf[y + j][i + x][2] = b;
            }
        }
    }
}

void draw_str(uint8_t *frame_buf[DISPLAY_HEIGHT][DISPLAY_WIDTH][3], char *str, int x, int y, uint8_t r, uint8_t g, uint8_t b, int spacing) {
    
}

// TODO functions:
// draw rect (x, y, width, height, color)
// draw line (x1, y1, x2, y2, color)
// draw bmp img (bmp, x, y)

int load_font(char *fname) {
    FILE * fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return 0;
    }
    size_t bytes_read = fread(font, 4, 128, fp);
    if (bytes_read != 128) {
        return 0;
    }
    return 1;
}