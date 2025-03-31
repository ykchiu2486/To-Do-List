#include "improvedTask.h"
#include <iostream>

int main() {
    AllTasks taskList;

    MoreTask* task1 = new MoreTask("Project A", "Work", false, Date(2025, 4, 10, 14), 1, 2, {});
    MoreTask* task2 = new MoreTask("Grocery Shopping", "Personal", false, Date(2025, 4, 5, 18), 2, 3, {});
    MoreTask* task3 = new MoreTask("Exercise", "Health", true, Date(2025, 4, 3, 7), 3, 1, {});

    taskList.add(task1);
    taskList.add(task2);
    taskList.add(task3);

    std::cout << "Task List:\n";
    taskList.showAll();

    return 0;
}
