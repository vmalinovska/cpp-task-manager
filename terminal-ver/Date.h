//
// Created by nika mally on 12/05/2026.
//

#ifndef DATE_H
#define DATE_H
#include <string>

class Date {
private:
    int day_;
    int month_;
    int year_;

    // checks whether given year is a leap year
    static bool isLeapYear(int year);

    // checks whether given day/month/year are correct according to rules of calendar
    static bool isCorrectDate(int day, int month, int year);

public:
    // a date constructor
    Date (int day, int month, int year);

    // sets new day/month/year if the values are correct
    // we have only one setter for the date, because by knowing all values
    // it is possible to check if the new date is correct
    void setDate(int day, int month, int year);

    // returns day of the date
    [[nodiscard]] int getDay() const {
        return day_;
    }

    // returns month of the date
    [[nodiscard]] int getMonth() const {
        return month_;
    }

    // returns year of the date
    [[nodiscard]] int getYear() const {
        return year_;
    }

    // returns date as a string
    [[nodiscard]] std::string toString() const {
        return std::to_string(day_) + "/" + std::to_string(month_) + "/" + std::to_string(year_);
    }

    // compares two dates
    bool operator==(const Date &other) const {
        return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
    }
};

#endif //DATE_H