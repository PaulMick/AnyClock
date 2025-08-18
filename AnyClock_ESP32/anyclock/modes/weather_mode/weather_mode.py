import time

# How often weather data is pulled from the API, in seconds
WEATHER_UPDATE_PERIOD = 60

class WeatherMode:
    def __init__(self, night: bool = False) -> None:
        self.night = night

        self.tempf: int = 0
        self.tempc: int = 0
        self.weather_code: int = 0
        self.humidity: int = 0

        self.year: int = 0
        self.month: int = 0
        
    def update(self, pressed: tuple[int], held: tuple[int]) -> bool:
        pass