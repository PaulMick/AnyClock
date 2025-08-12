MONTHS = [
    {
        "full": "JANUARY",
        "short": "JAN",
        "num": 1
    },
    {
        "full": "FEBRUARY",
        "short": "FEB",
        "num": 2
    },
    {
        "full": "MARCH",
        "short": "MAR",
        "num": 3
    },
    {
        "full": "APRIL",
        "short": "APR",
        "num": 4
    },
    {
        "full": "MAY",
        "short": "MAY",
        "num": 5
    },
    {
        "full": "JUNE",
        "short": "JUN",
        "num": 6
    },
    {
        "full": "JULY",
        "short": "JUL",
        "num": 7
    },
    {
        "full": "AUGUST",
        "short": "AUG",
        "num": 8
    },
    {
        "full": "SEPTEMBER",
        "short": "SEP",
        "num": 9
    },
    {
        "full": "OCTOBER",
        "short": "OCT",
        "num": 10
    },
    {
        "full": "NOVEMBER",
        "short": "NOV",
        "num": 11
    },
    {
        "full": "DECEMBER",
        "short": "DEC",
        "num": 12
    }
]

WEEK_DAYS = [
    {
        "full": "MONDAY",
        "short": "MON",
        "num": 0
    },
    {
        "full": "TUESDAY",
        "short": "TUE",
        "num": 1
    },
    {
        "full": "WEDNESDAY",
        "short": "WED",
        "num": 2
    },
    {
        "full": "THURSDAY",
        "short": "THU",
        "num": 3
    },
    {
        "full": "FRIDAY",
        "short": "FRI",
        "num": 4
    },
    {
        "full": "SATURDAY",
        "short": "SAT",
        "num": 5
    },
    {
        "full": "SUNDAY",
        "short": "SUN",
        "num": 6
    }
]

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