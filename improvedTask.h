#ifndef IMPROVEDTASK_H
#define IMPROVEDTASK_H

#include "basicTask.h"
#include "Date.h"
#include <vector>

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
        : Basic_task(other), deadline(other.deadline), priority(other.priority), status(other.status) {
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
        for(auto i : subTasks) {
            i->write(out);
        }
    }

    void show() {
        //TODO
    }


    void modify() {
        //TODO
    }
};

#endif // IMPROVEDTASK_H