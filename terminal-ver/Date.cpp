//
// Created by nika mally on 12/05/2026.
//

#include "Date.h"

#include <stdexcept>

bool Date::isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool Date::isCorrectDate(const int day, const int month, const int year) {
    // incorrect values
    if (month < 1 || month > 12) {
        return false;
    }
    if (year < 0) {
        return false;
    }

    int correctMonthEndDates[]  = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // February has 29 days if it is a leap year
    if (isLeapYear(year)) {
        correctMonthEndDates[1] = 29;
    }

    return day >= 1 && day <= correctMonthEndDates[month-1];
}

Date::Date(const int day, const int month, const int year) {
    if(!isCorrectDate(day, month, year)) {
        throw std::invalid_argument("Invalid date");
    }
    day_ = day;
    month_ = month;
    year_ = year;
}

void Date::setDate(const int day, const int month, const int year) {
    if(!isCorrectDate(day, month, year)) {
        throw std::invalid_argument("Invalid date");
    }
    day_ = day;
    month_ = month;
    year_ = year;
}

