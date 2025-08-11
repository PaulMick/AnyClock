import time

# How often weather data is pulled from the API, in seconds
WEATHER_UPDATE_PERIOD = 60

class ClockMode:
    def __init__(self, night: bool = False) -> None:
        self.night = night

        self.year: int = 0
        self.month: int = 0
        self.mday: int = 0
        self.wday: int = 0
        self.hour: int = 0
        self.minute: int = 0
        self.second: int = 0

        self.am: bool = True
        self.pm: bool = False

        self.tempf: int = 0
        self.tempc: int = 0

        self.weather_code = 0

        self.in_settings = False

    def update(self, pressed: list[int], held: list[int]) -> bool:
        # Handle settings

        # Update current local time
        local_time = time.localtime(time.time())

        self.year = local_time[0]
        self.month = local_time[1]
        self.mday = local_time[2]
        self.hour = local_time[3]
        self.minute = local_time[4]
        self.second = local_time[5]
        self.wday = local_time[6]