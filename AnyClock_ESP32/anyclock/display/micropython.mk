DISPLAY_MOD_DIR = /mnt/c/Users/paulw/Documents/Projects/AnyClock/Code/AnyClock/AnyClock_ESP32/anyclock/display
SRC_USERMOD_C += $(DISPLAY_MOD_DIR)/display_driver.c
SRC_USERMOD_C += $(DISPLAY_MOD_DIR)/display_manager.c
SRC_USERMOD_C += $(DISPLAY_MOD_DIR)/display_utils.c

CFLAGS_USERMOD += -I$(DISPLAY_MOD_DIR)