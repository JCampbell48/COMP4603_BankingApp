#include "Timestamp.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// Default constructor - current time
Timestamp::Timestamp() : timePoint(std::chrono::system_clock::now()) {
}

// Constructor from time_point
Timestamp::Timestamp(std::chrono::system_clock::time_point tp) : timePoint(tp) {
}

// Constructor from date/time components
Timestamp::Timestamp(int year, int month, int day, int hour, int minute, int second) {
    std::tm timeStruct = {};
    timeStruct.tm_year = year - 1900;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_mday = day;
    timeStruct.tm_hour = hour;
    timeStruct.tm_min = minute;
    timeStruct.tm_sec = second;

    std::time_t time = std::mktime(&timeStruct);
    timePoint = std::chrono::system_clock::from_time_t(time);
}

// Get underlying time_point
std::chrono::system_clock::time_point Timestamp::getTimePoint() const {
    return timePoint;
}

// Static factory method - current time
Timestamp Timestamp::now() {
    return Timestamp();
}

// Static factory method - from time_t
Timestamp Timestamp::fromTimeT(std::time_t time) {
    return Timestamp(std::chrono::system_clock::from_time_t(time));
}

// Get individual components
int Timestamp::getYear() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_year + 1900;
}

int Timestamp::getMonth() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_mon + 1;
}

int Timestamp::getDay() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_mday;
}

int Timestamp::getHour() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_hour;
}

int Timestamp::getMinute() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_min;
}

int Timestamp::getSecond() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);
    return local->tm_sec;
}

// Format as string: "YYYY-MM-DD HH:MM:SS"
std::string Timestamp::toString() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(4) << (local->tm_year + 1900) << "-"
       << std::setw(2) << (local->tm_mon + 1) << "-"
       << std::setw(2) << local->tm_mday << " "
       << std::setw(2) << local->tm_hour << ":"
       << std::setw(2) << local->tm_min << ":"
       << std::setw(2) << local->tm_sec;

    return ss.str();
}

// Format as date string: "YYYY-MM-DD"
std::string Timestamp::toDateString() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(4) << (local->tm_year + 1900) << "-"
       << std::setw(2) << (local->tm_mon + 1) << "-"
       << std::setw(2) << local->tm_mday;

    return ss.str();
}

// Format as time string: "HH:MM:SS"
std::string Timestamp::toTimeString() const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm* local = std::localtime(&time);

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << local->tm_hour << ":"
       << std::setw(2) << local->tm_min << ":"
       << std::setw(2) << local->tm_sec;

    return ss.str();
}

// Calculate days since another timestamp
double Timestamp::daysSince(const Timestamp& earlier) const {
    auto duration = timePoint - earlier.timePoint;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    return hours.count() / 24.0;
}

// Calculate hours since another timestamp
double Timestamp::hoursSince(const Timestamp& earlier) const {
    auto duration = timePoint - earlier.timePoint;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    return static_cast<double>(hours.count());
}

// Calculate seconds since another timestamp
double Timestamp::secondsSince(const Timestamp& earlier) const {
    auto duration = timePoint - earlier.timePoint;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    return static_cast<double>(seconds.count());
}

// Comparison operators
bool Timestamp::operator<(const Timestamp& other) const {
    return timePoint < other.timePoint;
}

bool Timestamp::operator>(const Timestamp& other) const {
    return timePoint > other.timePoint;
}

bool Timestamp::operator<=(const Timestamp& other) const {
    return timePoint <= other.timePoint;
}

bool Timestamp::operator>=(const Timestamp& other) const {
    return timePoint >= other.timePoint;
}

bool Timestamp::operator==(const Timestamp& other) const {
    return timePoint == other.timePoint;
}

bool Timestamp::operator!=(const Timestamp& other) const {
    return timePoint != other.timePoint;
}

// Convert to time_t
std::time_t Timestamp::toTimeT() const {
    return std::chrono::system_clock::to_time_t(timePoint);
}