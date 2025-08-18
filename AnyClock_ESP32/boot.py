import network
import os

os.system("source /anyclock.env")

wifi_ssid = os.getenv("WIFI_SSID")
wifi_key = os.getenv("WIFI_KEY")

if wifi_ssid == None or wifi_key == None:
    print("Unable to access wifi ssid and/or key from environment variables")
    exit()

sta_if = network.WLAN(network.WLAN.IF_STA)

if not sta_if.isconnected():
    sta_if.active(True)
    sta_if.connect(wifi_ssid, wifi_key)
    while not sta_if.isconnected():
        pass

print("Network config: ", sta_if.config("addr4"))