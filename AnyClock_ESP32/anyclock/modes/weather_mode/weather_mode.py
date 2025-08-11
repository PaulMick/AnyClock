import time

class WeatherMode:
    def __init__(self, night: bool = False) -> None:
        self.night = night

        self.tempf: int = 0
        self.tempc: int = 0
        self.weather_code: int = 0
        self.humidity: int = 0
        
    def update(self, pressed: list[int], held: list[int]) -> bool:
        pass