
#pragma once

#include <chrono>
#include <string>

/**
 * Timestamp - Class is used as a convenient wrapper around std::chrono for banking system
 */
class Timestamp {
private:
    std::chrono::system_clock::time_point timePoint;

public:
    // Constructors
    Timestamp();  // Current time
    explicit Timestamp(std::chrono::system_clock::time_point tp);
    Timestamp(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    // Get the underlying time_point (useful for interop)
    std::chrono::system_clock::time_point getTimePoint() const;

    // Static factory methods
    static Timestamp now();
    static Timestamp fromTimeT(std::time_t time);

    // Getters for individual components
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Formatting
    std::string toString() const;  // Format: "YYYY-MM-DD HH:MM:SS"
    std::string toDateString() const;  // Format: "YYYY-MM-DD"
    std::string toTimeString() const;  // Format: "HH:MM:SS"

    // Time calculations
    double daysSince(const Timestamp& earlier) const;
    double hoursSince(const Timestamp& earlier) const;
    double secondsSince(const Timestamp& earlier) const;

    // Comparison operators
    bool operator<(const Timestamp& other) const;
    bool operator>(const Timestamp& other) const;
    bool operator<=(const Timestamp& other) const;
    bool operator>=(const Timestamp& other) const;
    bool operator==(const Timestamp& other) const;
    bool operator!=(const Timestamp& other) const;

    // Conversion to time_t for compatibility
    std::time_t toTimeT() const;
};
