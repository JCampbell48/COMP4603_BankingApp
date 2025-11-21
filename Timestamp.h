
#pragma once
#include <string>

class Timestamp {
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;


    Timestamp();
    Timestamp(int year, int month, int day, int hour, int minute, int second);
    std::string toString();

};
