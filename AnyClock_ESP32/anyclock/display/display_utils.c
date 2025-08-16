#include <stdint.h>
#include <stdbool.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

const char *months_full[12] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
const char *months_short[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

const char *week_days_full[7] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
const char *week_days_short[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

const bool chars_3x5[128][5][3];