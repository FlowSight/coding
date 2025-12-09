#pragma once

namespace CarRental {

class Date {
public:
    int year, month, day;
    
    Date() : year(2025), month(1), day(1) {}
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>(const Date& other) const {
        return other < *this;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
};

} // namespace CarRental
