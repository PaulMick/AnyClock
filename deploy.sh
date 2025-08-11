source .env

# Ensure valid serial port
if [[ $1 =~ ^COM[0-9]$ ]]
then
    echo "Deploying project to ESP32 on port $1"
else
    echo "Error: Must specify valid serial port for deployment (e.g. \"COM1\")"
    exit 1
fi

$AMPY -p $1 put AnyClock_ESP32/main.py /main.py
$AMPY -p $1 put AnyClock_ESP32/boot.py /boot.py
$AMPY -p $1 put AnyClock_ESP32/anyclock /anyclock
$AMPY -p $1 put AnyClock_ESP32/anyclock.env /anyclock.env