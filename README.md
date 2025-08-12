# AnyClock
An flexible and customizable framework to turn an LED Matrix/ESP32 combo into a clock and more.

## Setup
Setting up this project is pretty simple. This project is targeted around a Windows developement system, so please keep that in mind.

### Environment Variables
Similar to how environment variables are handled in Flutter projects, environment variables used by the `deploy.sh` script will be stored in `.env`. Make a copy of `sample.env` and rename it to `.env`, then enter your environment variables in. `$PYTHON` and `$AMPY` should be the set to the file path to your `python.exe` and `ampy.exe` executables, respectively.

Likewise, environment variables used by the various microPython modules on the ESP32 will be stored in `AnyClock_ESP32/anyclock.env`. Make a copy of `sample-anyclock.env` in `AnyClock_ESP32` and rename it to `anyclock.env`, then enter your environment variables in.

### Install Python Requirements
Install the required developement dependencies (recommended to be done in a virtual environment)
```
pip install -r requirements.txt
```

### Flash microPython on ESP32
Download the appropriate microPython binary from the [MicroPython Website](https://micropython.org/download/#esp32).

Plug in your ESP32 and determine which serial port it is connected to with device manager.

Erase the current flash on the ESP32 (I used an ESP32-s3 for my project, if you are using a different ESP32 make sure to change the `--chip` flag appropriately)
```
python -m esptool --chip esp32-s3 erase-flash
```

Flash your microPython binary on the ESP32
```
python -m esptool --chip esp32-s3 --port $SERIAL_PORT write_flash -z 0x0000 $MICROPYTHON_BINARY
```
where `$SERIAL_PORT` looks like `COM1` and `$MICROPYTHON_BINARY` looks like `ESP32-GENERIC-S3-20250809-v1.26.0.bin`.

## Deployment
Plug in your ESP32 and determine which serial port it is connected to with device manager.

Deploy your project to your ESP32
```
bash ./deploy.sh $SERIAL_PORT
```
where `$SERIAL_PORT` looks like `COM1`.