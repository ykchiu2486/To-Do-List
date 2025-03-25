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
            file.close();
            return {};
        }

        int taskCount;
        if (!(file >> taskCount)) return {};

        std::vector<MoreTask*> tasks;
        tasks.reserve(taskCount);

        while (taskCount--) {
            std::string name, category;
            bool completed;
            int y, m, d, h, priority, status, subtaskCount;

            if (!(file >> name >> category >> completed >> y >> m >> d >> h >> priority >> status >> subtaskCount)) {
                break;
            }

            Date deadline(y, m, d, h);
            std::vector<Basic_task*> subtasks;
            
            while (subtaskCount--) {
                std::string subName, subCategory;
                bool subCo;
                
                if (!(file >> subName >> subCategory >> subCo)) {
                    break;
                }

                Basic_task* st = new Basic_task(subName, subCategory, subCo);
                subtasks.push_back(st);
            }

            MoreTask* task = new MoreTask(name, category, completed, deadline, priority, status, subtasks);
            tasks.push_back(task);
        }
        file.close();
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
    }
};
#endif //FILEIO_H