//DONE
#ifndef DATE_H
#define DATE_H
#include <ctime>
#include <iostream>
#include <fstream>
class Date {
private:
    int* year;
    int* month;
    int* day;
    int* hour;
public:
    Date() {
        year = new int;
        month = new int;
        day = new int;
        hour = new int;
        
        std::time_t* t = new std::time_t(std::time(nullptr));
        std::tm* now = std::localtime(t);
        *year = now->tm_year + 1900;
        *month = now->tm_mon + 1;
        *day = now->tm_mday;
        *hour = now->tm_hour;
        delete t;
    }
    
    Date(int y, int m, int d, int h) {
        year = new int(y);
        month = new int(m);
        day = new int(d);
        hour = new int(h);
    }
    
    ~Date() {
        delete year;
        delete month;
        delete day;
        delete hour;
    }
    
    bool operator>(const Date& other) const { // for AllTask::sort() to comapre
        if(*year != *other.year) return *year > *other.year;
        if(*month != *other.month) return *month > *other.month;
        if(*day != *other.day) return *day > *other.day;
        return *hour > *other.hour;
    }
    
    int operator-(const Date& other) const { //For the noticer to use(within 24 hours)
        std::tm* a = new std::tm();
        a->tm_year = *year - 1900;
        a->tm_mon = *month - 1;
        a->tm_mday = *day;
        a->tm_hour = *hour;
        
        std::tm* b = new std::tm();
        b->tm_year = *other.year - 1900;
        b->tm_mon = *other.month - 1;
        b->tm_mday = *other.day;
        b->tm_hour = *other.hour;
        
        std::time_t* time_a = new std::time_t(std::mktime(a));
        std::time_t* time_b = new std::time_t(std::mktime(b));
        
        int* result = new int(static_cast<int>(std::difftime(*time_a, *time_b) / 3600));
        
        delete a;
        delete b;
        delete time_a;
        delete time_b;
        
        int returnValue = *result;
        delete result;
        return returnValue;
    }
    
    void show() {
        std::cout << *year << "-" << *month << "-" << *day << " " << *hour << ":00";
    }
    
    void write(std::ostream& out) { //for Writer::write()
        out << *year << " " << *month << " " << *day << " " << *hour << " ";
    }

    Date(const Date& other) { // copy constructor
        year = new int(*other.year);
        month = new int(*other.month);
        day = new int(*other.day);
        hour = new int(*other.hour);
    }

    Date& operator=(const Date& other) { // copy constructor
        if (this != &other) {
            *year = *other.year;
            *month = *other.month;
            *day = *other.day;
            *hour = *other.hour;
        }
        return *this;
    }
};
#endif // DATE_H