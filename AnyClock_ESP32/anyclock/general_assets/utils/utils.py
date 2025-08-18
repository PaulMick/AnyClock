from enums.enums import *

def int_to_month_full(m: int) -> str:
    if m < 1 or m > 12:
        return ""
    return MONTHS[m]["full"]

def int_to_month_short(m: int) -> str:
    if m < 1 or m > 12:
        return ""
    return MONTHS[m]["short"]

def int_to_wday_full(d: int) -> str:
    if d < 0 or d > 6:
        return ""
    return WEEK_DAYS[d]["full"]

def int_to_wday_short(d: int) -> str:
    if d < 0 or d > 6:
        return ""
    return WEEK_DAYS[d]["short"]