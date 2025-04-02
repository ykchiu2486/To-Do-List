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
#include <limits>

using namespace std;

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

    MoreTask() : Basic_task("", "", false), deadline(), priority(3), status(3) {}

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
        out << *name << " " << *category << " " << (*completed ? "1" : "0") << " ";
        deadline.write(out);
        out << " " << priority << " " << status << " " << subTasks.size() << "\n";
        for (auto task : subTasks) {
            task->write(out);
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

    void show(bool notice = false)  {
        std::cout << std::left
                    << std::setw(20) << *name
                    << std::setw(15) << *category
                    << std::setw(10) << (*completed ? "Yes" : "No")
                    << std::setw(20) << getFormattedDeadline()
                    << std::setw(10) << (priority == 1 ? "High" : (priority == 2 ? "Medium" : "Low"))
                    << std::setw(15) << (status == 1 ? "Done" : (status == 2 ? "In Progress" : "Not Started"))
                    << std::setw(10) << subTasks.size() << (notice ? "\t*" : "")
                    << "\n";
    }

    void modify() {
        std::cout << "Select field to modify:\n";
        std::cout << "1. Name\n2. Category\n3. Completion Status\n4. Deadline\n5. Priority\n6. Status\n7. Modify Subtasks\n0. Cancel\n";
        int choice;
        std::cout << "Your choice: ";
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
            case 7: {
                if (subTasks.empty()) {
                    std::cout << "No subtasks available to modify.\n";
                } else {
                    std::cout << "Select a subtask to modify:\n";
                    for (size_t i = 0; i < subTasks.size(); ++i) {
                        std::cout << i + 1 << ". ";
                        subTasks[i]->show();
                    }
                    int subChoice;
                    std::cout << "Enter subtask number (or 0 to cancel): ";
                    std::cin >> subChoice;
                    if (subChoice > 0 && subChoice <= subTasks.size()) {
                        subTasks[subChoice - 1]->mod();
                    } else {
                        std::cout << "Invalid choice.\n";
                    }
                }
                break;
            }
            case 0: default: std::cout << "No changes made.\n"; break;
        }
    }

    Date getDeadline() {
        return deadline;
    }

    void makeNew() {
        for (Basic_task* task : subTasks) {
            delete task;
        }
        subTasks.clear();

        std::string tempName, tempCategory;
        int comp;
        std::cout << "Enter task name: ";
        std::cin >> tempName;
        std::cout << "Enter task category: ";
        std::cin >> tempCategory;
        std::cout << "Is the task completed? (1: Yes, 0: No): ";
        std::cin >> comp;
        bool tempCompleted = (comp == 1);

        int y, m, d, h;
        std::cout << "Enter deadline (format: YYYY MM DD HH): ";
        std::cin >> y >> m >> d >> h;
        deadline = Date(y, m, d, h);

        std::cout << "Enter priority (1: High, 2: Medium, 3: Low): ";
        std::cin >> priority;

        std::cout << "Enter task status (1: Done, 2: In Progress, 3: Not Started): ";
        std::cin >> status;

        delete name;
        delete category;
        delete completed;
        name = new std::string(tempName);
        category = new std::string(tempCategory);
        completed = new bool(tempCompleted);

        int subTaskCount;
        std::cout << "Enter number of subtasks: ";
        std::cin >> subTaskCount;
        for (int i = 0; i < subTaskCount; ++i) {
            std::cout << "----- Enter details for subtask " << i+1 << " -----\n";
            std::string stName, stCategory;
            int stComp;
            std::cout << "Enter subtask name: ";
            std::cin >> stName;
            std::cout << "Enter subtask category: ";
            std::cin >> stCategory;
            std::cout << "Is the subtask completed? (1: Yes, 0: No): ";
            std::cin >> stComp;
            bool stCompleted = (stComp == 1);
            subTasks.push_back(new Basic_task(stName, stCategory, stCompleted));
        }
        std::cout << "Task created successfully!\n";
    }

    void showThisTask() {
        std::cout << "===== Task Details =====\n";
        std::cout << "Name       : " << *name << "\n";
        std::cout << "Category   : " << *category << "\n";
        std::cout << "Completed  : " << (*completed ? "Yes" : "No") << "\n";
        std::cout << "Deadline   : " << getFormattedDeadline() << "\n";
        std::cout << "Priority   : " 
                    << (priority == 1 ? "High" : (priority == 2 ? "Medium" : "Low")) << "\n";
        std::cout << "Status     : " 
                    << (status == 1 ? "Done" : (status == 2 ? "In Progress" : "Not Started")) << "\n";
        std::cout << "Subtask Count: " << subTasks.size()  << "\n";
        
        if (!subTasks.empty()) {
            std::cout << "----- List of Subtasks -----\n";
            for (size_t i = 0; i < subTasks.size(); ++i) {
                std::cout << "Subtask " << i+1 << ":\n";
                subTasks[i]->show();
            }
        }
        std::cout << "==========================\n";
    }

    std::string getCategory() const { return *category; }
    int getPriority() const { return priority; }
    int getStatus() const { return status; }
};

class AllTasks {
private:
    std::vector<MoreTask*> alltask;
public:

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
                  << std::setw(10) << "Index"
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Category"
                  << std::setw(10) << "Completed"
                  << std::setw(20) << "Deadline"
                  << std::setw(10) << "Priority"
                  << std::setw(15) << "Status"
                  << std::setw(10) << "Subtasks"
                  << "\tNotice\n";
        std::cout << std::string(120, '-') << "\n";
        int* i = new int(0);
        for (auto task = alltask.begin(); task != alltask.end(); task++) {
            Date now;
            std::cout << std::setw(10) << *i;
            (*task)->show((*task)->getDeadline() - now <= 24);
            (*i)++;
        }
    }

    ~AllTasks() {
        for (auto i : alltask) {
            delete i;
        }
        alltask.clear();
    }
    
    AllTasks(std::vector<MoreTask*> tasks) {
        alltask = tasks;
    }

    void deleteTask(int index) {
        delete alltask[index];
        alltask.erase(alltask.begin() + index);
    }

    const std::vector<MoreTask*>& insideData() {
        return this->alltask;
    }

    void showByFilter() {
        cout << "Filter by (1: Category, 2: Priority, 3: Status): ";
        
        // 读取多选过滤条件
        vector<int> filters;
        string input;
        cin.ignore();
        getline(cin, input);
        istringstream iss(input);
        int filter;
        while (iss >> filter) {
            if (filter >= 1 && filter <= 3)
                filters.push_back(filter);
        }

        // 收集过滤参数
        string categoryFilter;
        int priorityFilter = -1;
        int statusFilter = -1;

        for (int f : filters) {
            switch (f) {
                case 1: 
                    cout << "Enter category: ";
                    getline(cin >> ws, categoryFilter);
                    break;
                case 2:
                    cout << "Enter priority (1-3): ";
                    while (!(cin >> priorityFilter) || priorityFilter < 1 || priorityFilter > 3) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid priority! Enter again (1-3): ";
                    }
                    break;
                case 3:
                    cout << "Enter status (1-3): ";
                    while (!(cin >> statusFilter) || statusFilter < 1 || statusFilter > 3) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid status! Enter again (1-3): ";
                    }
                    break;
            }
        }

        // 显示过滤结果
        cout << "\nFiltered Results:\n";
        std::cout << std::left
                  << std::setw(10) << "Index"
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Category"
                  << std::setw(10) << "Completed"
                  << std::setw(20) << "Deadline"
                  << std::setw(10) << "Priority"
                  << std::setw(15) << "Status"
                  << std::setw(10) << "Subtasks"
                  << "\tNotice\n";
        std::cout << std::string(120, '-') << "\n";
        Date now;
        for (size_t i = 0; i < alltask.size(); ++i) {
            MoreTask* task = alltask[i];
            
            bool match = true;
            if (!categoryFilter.empty() && task->getCategory() != categoryFilter)
                match = false;
            if (priorityFilter != -1 && task->getPriority() != priorityFilter)
                match = false;
            if (statusFilter != -1 && task->getStatus() != statusFilter)
                match = false;

            if (match) {
                cout << setw(10) << i;
                task->show((task->getDeadline() - now <= 24));
            }
        }
    }
};

#endif // IMPROVEDTASK_H
