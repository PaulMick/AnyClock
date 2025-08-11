print("Starting main.py")

import neopixel
from machine import Pin
from time import sleep

count = 100

np = neopixel.NeoPixel(Pin(48), 1)

while count > 0:
    print(count)
    count -= 1
    np[0] = (255, 0, 0)
    sleep(0.3)
    np[0] = (0, 255, 0)
    sleep(0.3)
    np[0] = (0, 0, 255)
    sleep(0.3)
    

print("End main.py")