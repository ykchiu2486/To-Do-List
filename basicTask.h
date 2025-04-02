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

    Basic_task() {}

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
        out << (*name) << "\n" << (*category) << " " << (*completed) << "\n";
    }

    virtual void show(bool notice = false) {
        std::cout << "  [Basic_task] Name: " << *name 
                  << ", Category: " << *category 
                  << ", Completed: " << (*completed ? "Yes" : "No") << "\n";
    }

    void mod() {
        std::cout << "Modify Basic Task:\n";
        std::cout << "1. Name\n2. Category\n3. Completion Status\n0. Cancel\n";
        int choice;
        std::cout << "Your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "New Name: ";
                std::cin.ignore();
                std::getline(std::cin, *name);
                break;
            }
            case 2: {
                std::cout << "New Category: ";
                std::cin.ignore();
                std::getline(std::cin, *category);
                break;
            }
            case 3: {
                int comp;
                std::cout << "Completed (1: Yes, 0: No): ";
                std::cin >> comp;
                *completed = (comp == 1);
                break;
            }
            case 0:
            default:
                std::cout << "No changes made.\n";
                break;
        }
    }
};

#endif // BASICTASK_H
