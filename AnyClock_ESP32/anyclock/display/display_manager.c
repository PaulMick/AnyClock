#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display_driver.h"
#include "display_utils.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define FONT_NAME "5x5_flex.font"

int load_font_result = load_font(FONT_NAME);
if (load_font_result) {
    printf("Loaded font \"%s\" successfully\n", FONT_NAME);
} else {
    printf("Failed to load font \"%s\"\n", FONT_NAME);
}

struct DisplayHandle display_handle = get_display_handle();

static mp_obj_t display_state_bytes(mp_obj_t bytes) {

}