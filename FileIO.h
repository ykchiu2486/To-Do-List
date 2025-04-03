//TODO
#ifndef FILEIO_H
#define FILEIO_H

#include "improvedTask.h"
#include "basicTask.h"
#include <fstream>
#include <vector>

class Reader {
private:
    std::string filename;
public:
    Reader(std::string name) : filename(name) {}

    std::vector<MoreTask*> read() {
        std::ifstream file(this->filename);
        if (!file.good()) {
            std::cerr << "Add a new task!\n" << std::endl;
            return {};
        }
    
        int taskCount;
        file >> taskCount;
        file.ignore();  
    
        std::vector<MoreTask*> tasks;
        while (taskCount--) {
            std::string name, category;
            bool completed;
            int y, m, d, h, priority, status, subtaskCount;
    
            std::getline(file >> std::ws, name);
    
            if (!(file >> category >> completed >> y >> m >> d >> h >> priority >> status >> subtaskCount)) {
                std::cerr << "Fail to read tasks\n" << std::endl;
                exit(1);
            }
            file.ignore(); 
    
            std::vector<Basic_task*> subtasks;
            while (subtaskCount--) {
                std::string subName, subCategory;
                bool subCompleted;
                std::getline(file >> std::ws, subName);
                if (!(file >> subCategory >> subCompleted)) {
                    std::cerr << "Fail to read subtasks!\n" << std::endl;
                    exit(1);
                }
                file.ignore();  
                subtasks.push_back(new Basic_task(subName, subCategory, subCompleted));
            }
    
            tasks.push_back(new MoreTask(name, category, completed, Date(y, m, d, h), priority, status, subtasks));
        }
        return tasks;
    }
};

class Writer {
private:
    std::string filename;

public:
    Writer(std::string name) {
        filename = name;
    }

    void write(const std::vector<MoreTask*>& tasks) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        file << tasks.size() << "\n";
        for(auto i : tasks) {
            i->write(file);
        }
        file.close();
    }
};
#endif //FILEIO_H