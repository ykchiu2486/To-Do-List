#ifndef IMPROVEDTASK_H
#define IMPROVEDTASK_H

#include "basicTask.h"
#include "Date.h"
#include <string>
#include <iostream>
#include <vector>

class MoreTask : public Basic_task {    
protected:
    Date deadline;
    int priority; //high medium low
    int status; //In progress, Done, postpone, not start (maybe when it turn to done should remove from list)
    int checkType; //check just need startTime or both?
    std::vector<Basic_task> subTasks;

};

#endif //IMPROVEDTASK_H