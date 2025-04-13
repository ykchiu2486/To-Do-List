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
    std::vector<MoreTask*> read() {
        std::ifstream* file = new std::ifstream(*this->filename);
        if (!file->good()) {
            std::cerr << "Add a new task!\n" << std::endl;
            delete file;
            return {};
        }
        int* taskCount = new int;
        *file >> *taskCount;
        file->ignore();
        std::vector<MoreTask*> tasks;
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
            if (!(*file >> *category >> *completed >> *y >> *m >> *d >> *h >> *priority >> *status >> *subtaskCount)) {
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
            while ((*currentSubtaskCount)--) {
                std::string* subName = new std::string();
                std::string* subCategory = new std::string();
                bool* subCompleted = new bool;
                std::getline(*file >> std::ws, *subName);
                if (!(*file >> *subCategory >> *subCompleted)) {
                    std::cerr << "Fail to read subtasks!\n" << std::endl;
                    // 清理内存
                    delete subName;
                    delete subCategory;
                    delete subCompleted;
                    delete currentSubtaskCount;
                    // 清理已创建的 subtasks
                    for (auto subtask : *subtasks) {
                        delete subtask;
                    }
                    delete subtasks;
                    // 清理其他变量
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
            
            // 創建臨時 Date 對象而不是直接使用 Date 構造函數
            Date* tempDate = new Date(*y, *m, *d, *h);
            tasks.push_back(new MoreTask(*name, *category, *completed, *tempDate, *priority, *status, *subtasks));
            delete tempDate;
            
            // 現在 MoreTask 已擁有 subtasks 的副本，不應刪除 subtasks 向量本身
            // 但也不應讓它指向的對象洩漏
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

class Writer {
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
        for(auto i : tasks) {
            i->write(*file);
        }
        file->close();
        delete file;
    }
};
#endif //FILEIO_H