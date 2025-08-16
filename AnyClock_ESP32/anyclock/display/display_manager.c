#include <stdio.h>
#include <stdlib.h>
#include "display_driver.h"
#include "display_utils.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "py/objstr.h"

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

struct DisplayHandle display_handle = get_display_handle();

static mp_obj_t display_state_bytes(mp_obj_t bytes) {

}