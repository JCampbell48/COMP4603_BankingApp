#include "Timestamp.h"
#include <ctime>

Timestamp::Timestamp(){
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;
}


Timestamp::Timestamp(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
}
