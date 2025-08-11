from machine import Pin
import time
import ujson
from general_assets.enums.enums import *

from modes.clock_mode.clock_mode import ClockMode
from modes.weather_mode.weather_mode import WeatherMode

MENU_PIN = 1
SETTINGS_PIN = 2
UP_PIN = 3
DOWN_PIN = 4
LEFT_PIN = 5
RIGHT_PIN = 6

def run() -> None:
    with open("mode_manager_state.json", "r") as f:
        current_state = ujson.load(f)

    modes = {
        MODE_CLOCK: ClockMode(current_state["night"]),
        MODE_WEATHER: WeatherMode(current_state["night"])
    }

    prev_inputs = []
    inputs = []

    # Main update loop
    while True:
        # Inputs
        

        # Mode selection menu
        if current_state["in_menu"]:
            #TODO
            pass

        