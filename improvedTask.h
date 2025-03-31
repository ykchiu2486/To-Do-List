#ifndef IMPROVEDTASK_H
#define IMPROVEDTASK_H

#include "basicTask.h"
#include "Date.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class MoreTask : public Basic_task {
protected:
    Date deadline;
    int priority;
    int status;
    std::vector<Basic_task*> subTasks;

public:
    MoreTask(std::string name, std::string category, bool completed,
             Date deadline, int priority, int status,
             std::vector<Basic_task*> subTasks)
        : Basic_task(name, category, completed),
          deadline(deadline), priority(priority), status(status), subTasks(subTasks) {}

    MoreTask(const MoreTask& other)
        : Basic_task(other), deadline(other.deadline),
          priority(other.priority), status(other.status) {
        for (Basic_task* task : other.subTasks) {
            subTasks.push_back(new Basic_task(*task));
        }
    }

    MoreTask& operator=(const MoreTask& other) {
        if (this != &other) {
            Basic_task::operator=(other);
            deadline = other.deadline;
            priority = other.priority;
            status = other.status;

            for (Basic_task* task : subTasks) {
                delete task;
            }
            subTasks.clear();

            for (Basic_task* task : other.subTasks) {
                subTasks.push_back(new Basic_task(*task));
            }
        }
        return *this;
    }

    ~MoreTask() override {
        for (Basic_task* task : subTasks) {
            delete task;
        }
        subTasks.clear();
    }

    void write(std::ofstream& out) {
        out << *name << " " << *category << " " << *completed << " ";
        deadline.write(out);
        out << priority << " " << status << " " << subTasks.size() << "\n";
        for (auto i : subTasks) {
            i->write(out);
        }
    }

    std::string getFormattedDeadline() const {
        std::ostringstream tempStream;
        Date tempDeadline = deadline;  
        tempDeadline.write(tempStream);
        std::string tempStr = tempStream.str();
        std::istringstream iss(tempStr);
        int y, m, d, h;
        iss >> y >> m >> d >> h;
        std::ostringstream oss;
        oss << std::setw(4) << std::setfill('0') << y << "-"
            << std::setw(2) << std::setfill('0') << m << "-"
            << std::setw(2) << std::setfill('0') << d << " "
            << std::setw(2) << std::setfill('0') << h << ":00";
        return oss.str();
    }

    void show() {
        std::cout << std::left
                  << std::setw(20) << *name
                  << std::setw(15) << *category
                  << std::setw(10) << (*completed ? "Yes" : "No")
                  << std::setw(20) << getFormattedDeadline()
                  << std::setw(10) << (priority == 1 ? "High" : (priority == 2 ? "Medium" : "Low"))
                  << std::setw(15) << (status == 1 ? "Done" : (status == 2 ? "In Progress" : "Not Started"))
                  << std::setw(10) << subTasks.size()
                  << "\n";
    }

    void modify() {
        std::cout << "Select field to modify:\n";
        std::cout << "1. Name\n2. Category\n3. Completion Status\n4. Deadline\n5. Priority\n6. Status\n0. Cancel\n";
        int choice;
        std::cin >> choice;

        switch(choice) {
            case 1: { std::cout << "New Name: "; std::cin >> *name; break; }
            case 2: { std::cout << "New Category: "; std::cin >> *category; break; }
            case 3: { 
                int comp; 
                std::cout << "Completed (1: Yes, 0: No): "; 
                std::cin >> comp; 
                *completed = (comp == 1); 
                break; 
            }
            case 4: { 
                int y, m, d, h; 
                std::cout << "New Deadline (YYYY MM DD HH): "; 
                std::cin >> y >> m >> d >> h; 
                deadline = Date(y, m, d, h); 
                break; 
            }
            case 5: { std::cout << "New Priority (1: High, 2: Medium, 3: Low): "; std::cin >> priority; break; }
            case 6: { std::cout << "New Status (1: Done, 2: In Progress, 3: Not Started): "; std::cin >> status; break; }
            case 0: default: std::cout << "No changes made.\n"; break;
        }
    }
};

class AllTasks {
public:
    std::vector<MoreTask*> alltask;

    void add(MoreTask* task) {
        alltask.push_back(task);
    }

    MoreTask*& operator[](size_t index) {
        return alltask[index];
    }

    const MoreTask* operator[](size_t index) const {
        return alltask[index];
    }

    void showAll() {
        std::cout << std::left
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Category"
                  << std::setw(10) << "Completed"
                  << std::setw(20) << "Deadline"
                  << std::setw(10) << "Priority"
                  << std::setw(15) << "Status"
                  << std::setw(10) << "Subtasks"
                  << "\n";
        std::cout << std::string(100, '-') << "\n";
        for (auto& task : alltask) {
            task->show();
        }
    }

    ~AllTasks() {
        for (auto i : alltask) {
            delete i;
        }
        alltask.clear();
    }
};

#endif // IMPROVEDTASK_H
