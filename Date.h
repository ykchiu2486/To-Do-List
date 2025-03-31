#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>
#include <fstream>

class Date {
private:
    int year;
    int month;
    int day;
    int hour;

public:
    Date() {
        std::time_t t = std::time(nullptr); 
        std::tm* now = std::localtime(&t); 
        
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        hour = now->tm_hour;
    }

    Date(int y, int m, int d, int h) : year(y), month(m), day(d), hour(h) {}

    bool operator>(const Date& other) const {
        if(year != other.year) return year > other.year;
        if(month != other.month) return month > other.month;
        if(day != other.day) return day > other.day;
        return hour > other.hour;
    }

    int operator-(const Date& other) const {
        std::tm a = {};
        a.tm_year = year - 1900;
        a.tm_mon = month - 1;
        a.tm_mday = day;
        a.tm_hour = hour;

        std::tm b = {};
        b.tm_year = other.year - 1900;
        b.tm_mon = other.month - 1;
        b.tm_mday = other.day;
        b.tm_hour = other.hour;

        std::time_t time_a = std::mktime(&a);
        std::time_t time_b = std::mktime(&b);
        
        return static_cast<int>(std::difftime(time_a, time_b) / 3600);
    }

    void show() {
        std::cout << year << "-" << month << "-" << day << " " << hour << ":00"; 
    }

    // 修改此函式，讓它接受 std::ostream 以便同時支援 ofstream 與 ostringstream
    void write(std::ostream& out) {
        out << year << " " << month << " " << day << " " << hour << " "; 
    }
};

#endif // DATE_H
