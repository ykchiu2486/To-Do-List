#ifndef DATE_H
#define DATE_H

#include <ctime>

struct Date {
    int year;
    int month;
    int day;
    int hour;

    
    Date() {
        std::time_t t = std::time(nullptr); 
        std::tm* now = std::localtime(&t); 
        
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        hour = now->tm_hour;
    }

    Date(int y, int m, int d, int h) : year(y), month(m), day(d), hour(h) {}

};

#endif // DATE_H
