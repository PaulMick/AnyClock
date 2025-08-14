from machine import Pin
import time
import ujson
from general_assets.enums.enums import *


from modes.clock_mode.clock_mode import ClockMode
from modes.weather_mode.weather_mode import WeatherMode

PIN_MENU = 1
PIN_SELECT = 2
PIN_UP = 3
PIN_DOWN = 4
PIN_LEFT = 5
PIN_RIGHT = 6

prev_inputs = (0, 0, 0, 0, 0, 0)
inputs = (0, 0, 0, 0, 0, 0)

menu_pin = Pin(PIN_MENU, Pin.IN)
select_pin = Pin(PIN_SELECT, Pin.IN)
up_pin = Pin(PIN_UP, Pin.IN)
down_pin = Pin(PIN_DOWN, Pin.IN)
left_pin = Pin(PIN_LEFT, Pin.IN)
right_pin = Pin(PIN_RIGHT, Pin.IN)

def run() -> None:
    with open("mode_manager_state.json", "r") as f:
        current_state = ujson.load(f)

    modes = {
        MODE_CLOCK: ClockMode(current_state["night"]),
        MODE_WEATHER: WeatherMode(current_state["night"])
    }

    # Main update loop
    while True:
        # Inputs
        prev_inputs = inputs
        inputs = get_input()
        pressed = tuple(1 if inputs[i] == 1 and prev_inputs[i] == 0 else 0 for i in range(len(inputs)))

        # Mode selection menu
        if current_state["in_menu"]:
            #TODO
            pass
        # Update current mode
        else:
            modes[current_state["mode_id"]].update(pressed, inputs)

def get_input() -> tuple[int]:
    return (menu_pin.value(), select_pin.value(), up_pin.value(), down_pin.value(), left_pin.value(), right_pin.value())