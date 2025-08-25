import network
import os
from anyclock.secrets import *

if WIFI_SSID == None or WIFI_KEY == None:
    print("Unable to access wifi ssid and/or key from environment variables")
    exit()

sta_if = network.WLAN(network.WLAN.IF_STA)

if not sta_if.isconnected():
    sta_if.active(True)
    sta_if.connect(WIFI_SSID, WIFI_KEY)
    while not sta_if.isconnected():
        pass

print("Network config: ", sta_if.config("addr4"))