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
#include <algorithm>

using namespace std;

int safeIntInput(const string& prompt, int min, int max) {
    int value;
    bool validInput = false;
    
    do {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer between " << min << " and " << max << ".\n";
        }
    } while (!validInput);
    
    return value;
}

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
        out << *name << "\n" << *category << " " << (*completed ? "1" : "0") << " ";
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

    void modify() override{
        std::cout << "Select field to modify:\n";
        std::cout << "1. Name\n2. Category\n3. Completion Status\n4. Deadline\n5. Priority\n6. Status\n7. Modify Subtasks\n0. Cancel\n";
        
        int choice = safeIntInput("Your choice: ", 0, 7);

        switch(choice) {
            case 1: { 
                *name = safeStringInput("New Name: "); 
                break; 
            }            
            case 2: { 
                *category = safeStringInput("New Category: "); 
                break; 
            }
            case 3: { 
                int comp = safeIntInput("Completed (1: Yes, 0: No): ", 0, 1);
                *completed = (comp == 1); 
                break; 
            }
            case 4: { 
                int y, m, d, h;
                cout << "New Deadline (YYYY MM DD HH): ";
                bool validDate = false;
                do {
                    if (cin >> y >> m >> d >> h) {
                        if (y >= 2000 && y <= 2100 && m >= 1 && m <= 12 && 
                            d >= 1 && d <= 31 && h >= 0 && h <= 23) {
                            validDate = true;
                        } else {
                            cout << "Invalid date or time. Please try again: ";
                        }
                    } else {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Format: YYYY MM DD HH: ";
                    }
                } while (!validDate);
                
                deadline = Date(y, m, d, h);
                break; 
            }
            case 5: { 
                priority = safeIntInput("New Priority (1: High, 2: Medium, 3: Low): ", 1, 3);
                break; 
            }
            case 6: { 
                status = safeIntInput("New Status (1: Done, 2: In Progress, 3: Not Started): ", 1, 3);
                break; 
            }
            case 7: {
                if (subTasks.empty()) {
                    std::cout << "No subtasks available to modify.\n";
                } else {
                    std::cout << "Select a subtask to modify:\n";
                    for (size_t i = 0; i < subTasks.size(); ++i) {
                        std::cout << i + 1 << ". ";
                        subTasks[i]->show();
                    }
                    
                    int subChoice = safeIntInput("Enter subtask number (or 0 to cancel): ", 0, static_cast<int>(subTasks.size()));
                    
                    if (subChoice > 0) {
                        subTasks[subChoice - 1]->modify();
                    } else {
                        std::cout << "Operation cancelled.\n";
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

        std::string tempName = safeStringInput("Enter task name: ");
        std::string tempCategory = safeStringInput("Enter task category: ");
        int comp = safeIntInput("Is the task completed? (1: Yes, 0: No): ", 0, 1);
        bool tempCompleted = (comp == 1);

        int y, m, d, h;
        bool validDate = false;
        cout << "Enter deadline (format: YYYY MM DD HH): ";
        do {
            if (cin >> y >> m >> d >> h) {
                if (y >= 2000 && y <= 2100 && m >= 1 && m <= 12 && 
                    d >= 1 && d <= 31 && h >= 0 && h <= 23) {
                    validDate = true;
                } else {
                    cout << "Invalid date or time. Please try again: ";
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Format: YYYY MM DD HH: ";
            }
        } while (!validDate);
        
        deadline = Date(y, m, d, h);
        priority = safeIntInput("Enter priority (1: High, 2: Medium, 3: Low): ", 1, 3);
        status = safeIntInput("Enter task status (1: Done, 2: In Progress, 3: Not Started): ", 1, 3);

        delete name;
        delete category;
        delete completed;
        name = new std::string(tempName);
        category = new std::string(tempCategory);
        completed = new bool(tempCompleted);

        int subTaskCount = safeIntInput("Enter number of subtasks (0-10): ", 0, 10);
        
        for (int i = 0; i < subTaskCount; ++i) {
            std::cout << "----- Enter details for subtask " << i+1 << " -----\n";
            std::string stName = safeStringInput("Enter subtask name: ");
            std::string stCategory = safeStringInput("Enter subtask category: ");
            int stComp = safeIntInput("Is the subtask completed? (1: Yes, 0: No): ", 0, 1);
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
        delete i; 
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
        if (index >= 0 && index < alltask.size()) {
            delete alltask[index];
            alltask.erase(alltask.begin() + index);
        } else {
            cout << "Invalid index. No task deleted.\n";
        }
    }

    const std::vector<MoreTask*>& insideData() {
        return this->alltask;
    }

    void showByFilter() {
        cout << "Filter by (1: Category, 2: Priority, 3: Status): ";
        
        vector<int> filters;
        string input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        istringstream iss(input);
        int filter;
        while (iss >> filter) {
            if (filter >= 1 && filter <= 3)
                filters.push_back(filter);
        }
        
        if (filters.empty()) {
            cout << "No valid filters entered. Showing all tasks.\n";
            showAll();
            return;
        }

        string categoryFilter;
        int priorityFilter = -1;
        int statusFilter = -1;

        for (int f : filters) {
            switch (f) {
                case 1: 
                    cout << "Enter category: ";
                    getline(cin, categoryFilter);
                    break;
                case 2:
                    priorityFilter = safeIntInput("Enter priority (1: High, 2: Medium, 3: Low): ", 1, 3);
                    break;
                case 3:
                    statusFilter = safeIntInput("Enter status (1: Done, 2: In Progress, 3: Not Started): ", 1, 3);
                    break;
            }
        }

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
        bool noMatches = true;
        
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
                noMatches = false;
            }
        }
        
        if (noMatches) {
            cout << "No tasks match the specified filters.\n";
        }
    }

    void sort() {
        std::sort(alltask.begin(), alltask.end(), [](MoreTask* a, MoreTask* b) {
            if (a->getPriority() != b->getPriority()) {
                return a->getPriority() < b->getPriority();
            } else {
                return (a->getDeadline() - b->getDeadline()) < 0;
            }
        });
    }
    
    size_t size() const {
        return alltask.size();
    }
};

#endif // IMPROVEDTASK_H
