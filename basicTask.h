#ifndef BASICTASK_H
#define BASICTASK_H

#include <iostream>
#include <string>

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

    virtual ~Basic_task() {
        delete name;
        delete category;
        delete completed;
    }

    void show() {
        std::cout << *name << "\t" << *category << "\t" << (*completed ? "true" : "false") << "\n";
    }
};

#endif // BASICTASK_H
