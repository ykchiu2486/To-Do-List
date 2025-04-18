//DONE
#ifndef FILEIO_H
#define FILEIO_H
#include "improvedTask.h"
#include "basicTask.h"
#include <fstream>
#include <vector>
class Reader {
private:
    std::string* filename;
public:
    Reader(std::string name) {
        filename = new std::string(name);
    }
    ~Reader() {
        delete filename;
    }
    std::vector<MoreTask*>* read() { // the most important part of this homework
        std::ifstream* file = new std::ifstream(*this->filename);
        if (!file->good()) { //check whether file exist
            std::cerr << "Add a new task!\n" << std::endl;
            delete file;
            return new vector<MoreTask*>(0);
        }
        int* taskCount = new int;
        *file >> *taskCount;
        file->ignore();
        std::vector<MoreTask*>* tasks = new std::vector<MoreTask*>;
        while ((*taskCount)--) {
            std::string* name = new std::string();
            std::string* category = new std::string();
            bool* completed = new bool;
            int* y = new int;
            int* m = new int;
            int* d = new int;
            int* h = new int;
            int* priority = new int;
            int* status = new int;
            int* subtaskCount = new int;
            std::getline(*file >> std::ws, *name);
            if (!(*file >> *category >> *completed >> *y >> *m >> *d >> *h >> *priority >> *status >> *subtaskCount)) { // if the txt file doesn't meet the format
                std::cerr << "Fail to read tasks\n" << std::endl;
                delete name;
                delete category;
                delete completed;
                delete y;
                delete m;
                delete d;
                delete h;
                delete priority;
                delete status;
                delete subtaskCount;
                delete file;
                delete taskCount;
                exit(1);
            }
            file->ignore();
            std::vector<Basic_task*>* subtasks = new std::vector<Basic_task*>();
            int* currentSubtaskCount = new int(*subtaskCount);
            while ((*currentSubtaskCount)--) { //handle the  subtasks
                std::string* subName = new std::string();
                std::string* subCategory = new std::string();
                bool* subCompleted = new bool;
                std::getline(*file >> std::ws, *subName);
                if (!(*file >> *subCategory >> *subCompleted)) {
                    std::cerr << "Fail to read subtasks!\n" << std::endl;
                    delete subName;
                    delete subCategory;
                    delete subCompleted;
                    delete currentSubtaskCount;
                    for(auto subtask = subtasks->begin(); subtask != subtasks->end(); subtask++) {
                        delete *subtask;
                    }
                    delete subtasks;
                    delete name;
                    delete category;
                    delete completed;
                    delete y;
                    delete m;
                    delete d;
                    delete h;
                    delete priority;
                    delete status;
                    delete subtaskCount;
                    delete file;
                    delete taskCount;
                    exit(1);
                }
                file->ignore();
                subtasks->push_back(new Basic_task(*subName, *subCategory, *subCompleted));
                delete subName;
                delete subCategory;
                delete subCompleted;
            }
            delete currentSubtaskCount;
            
            Date* tempDate = new Date(*y, *m, *d, *h);
            tasks->push_back(new MoreTask(*name, *category, *completed, *tempDate, *priority, *status, *subtasks));
            delete tempDate;
            

            delete subtasks;
            
            delete name;
            delete category;
            delete completed;
            delete y;
            delete m;
            delete d;
            delete h;
            delete priority;
            delete status;
            delete subtaskCount;
        }
        delete taskCount;
        delete file;
        return tasks;
    }
};

class Writer { //use other class's write() function
private:
    std::string* filename;
public:
    Writer(std::string name) {
        filename = new std::string(name);
    }
    ~Writer() {
        delete filename;
    }
    void write(const std::vector<MoreTask*>& tasks) {
        std::ofstream* file = new std::ofstream(*filename);
        if (!file->is_open()) {
            std::cerr << "Failed to open file: " << *filename << std::endl;
            delete file;
            return;
        }
        *file << tasks.size() << "\n";
        for(auto i = tasks.begin(); i != tasks.end(); i++) {
            (*i)->write(*file);
        }
        file->close();
        delete file;
    }
};
#endif //FILEIO_H