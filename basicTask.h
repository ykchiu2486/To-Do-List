#ifndef BASICTASK_H
#define BASICTASK_H

#include <iostream>
#include <string>
#include <fstream>

class Basic_task {
protected:
    std::string* name;
    std::string* category;
    bool* completed;

public:
    Basic_task(std::string Pname, std::string Pcategory, bool Pcompleted) {
        name = new std::string(Pname);
        category = new std::string(Pcategory);
        completed = new bool(Pcompleted);
    }

    Basic_task(const Basic_task& other) {
        name = new std::string(*other.name);
        category = new std::string(*other.category);
        completed = new bool(*other.completed);
    }

    Basic_task& operator=(const Basic_task& other) {
        if (this != &other) {
            delete name;
            delete category;
            delete completed;

            name = new std::string(*other.name);
            category = new std::string(*other.category);
            completed = new bool(*other.completed);
        }
        return *this;
    }

    virtual ~Basic_task() {
        delete name;
        delete category;
        delete completed;
    }

    void write(std::ofstream &out) {
        out << (*name) << " " << (*category) << " " << (*completed) << "\n";
    }
};

#endif // BASICTASK_H
