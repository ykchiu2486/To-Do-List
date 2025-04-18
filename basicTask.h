#ifndef BASICTASK_H
#define BASICTASK_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

class Basic_task {
    protected:
        std::string* name;
        std::string* category;
        bool* completed;
        
        std::string* safeStringInput(const std::string& prompt) { //input-validation
            std::string* input = new std::string();
            std::cout << prompt;
            if (std::cin.peek() == '\n') { //read one line
                std::cin.ignore();
            }
            std::getline(std::cin, *input);
            return input;
        }
        
        bool* safeBoolInput(const std::string& prompt) { //input-validation
            int* value = new int;
            bool* validInput = new bool(false);
            do {
                std::cout << prompt;
                if (std::cin >> *value && (*value == 0 || *value == 1)) {
                    *validInput = true;
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter 0 (No) or 1 (Yes).\n";
                }
            } while (!*validInput);
            
            bool* result = new bool(*value == 1);
            delete value;
            delete validInput;
            return result;
        }
        
        int* safeIntInput(const std::string& prompt, int min, int max) { //input-validation
            int* value = new int;
            bool* validInput = new bool(false);
            do {
                std::cout << prompt;
                if (std::cin >> *value && *value >= min && *value <= max) { //check 
                    *validInput = true;
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a integer between " << min << " and " << max << ".\n";
                }
            } while (!*validInput);
            
            delete validInput;
            return value;
        }
        
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
        
        Basic_task() {
            name = new std::string("");
            category = new std::string("");
            completed = new bool(false);
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
        
        void write(std::ofstream &out) { //for Writer::write()
            out << (*name) << "\n" << (*category) << " " << (*completed) << "\n";
        }
        
        virtual void show(bool notice = false) {
            std::cout << " [Basic_task] Name: " << *name
                      << ", Category: " << *category
                      << ", Completed: " << (*completed ? "Yes" : "No") << "\n";
        }
        
        virtual void modify() {
            std::cout << "Modify Basic Task:\n";
            std::cout << "1. Name\n2. Category\n3. Completion Status\n0. Cancel\n";
            int* choice = safeIntInput("Your choice: ", 0, 3);
            
            switch (*choice) {
                case 1: {
                    name = safeStringInput("New Name: ");
                    break;
                }
                case 2: {
                    category = safeStringInput("New Category: ");
                    break;
                }
                case 3: {
                    *completed = safeBoolInput("Completed (1: Yes, 0: No): ");
                    break;
                }
                case 0:
                default:
                    std::cout << "No changes made.\n";
                    break;
            }
            delete choice;
        }
    };
#endif // BASICTASK_H