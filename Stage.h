//DONE
#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include "improvedTask.h"
#include "Date.h"
using std::cout;

class Stage { // this object try to manage the apperance of the whole terminal
private:
    void bigTitle() {
        cout << "████████╗ ██████╗ ██████╗  ██████╗     ██╗     ██╗███████╗████████╗\n";
        cout << "╚══██╔══╝██╔═══██╗██╔══██╗██╔═══██╗    ██║     ██║██╔════╝╚══██╔══╝\n";
        cout << "   ██║   ██║   ██║██║  ██║██║   ██║    ██║     ██║███████╗   ██║   \n";
        cout << "   ██║   ██║   ██║██║  ██║██║   ██║    ██║     ██║╚════██║   ██║   \n";
        cout << "   ██║   ╚██████╔╝██████╔╝╚██████╔╝    ███████╗██║███████║   ██║   \n";
        cout << "   ╚═╝    ╚═════╝ ╚═════╝  ╚═════╝     ╚══════╝╚═╝╚══════╝   ╚═╝   \n";
    }

    void nowDate() {
        Date* newDate = new Date;
        newDate->show();
        delete newDate;
    }

    void seperator() {
        std::cout << std::string(120, '-') << "\n";
    }

public:
    void banner() {
        bigTitle();
        seperator();
        cout << "Now: ";
        nowDate();
        cout << "\n";
        seperator();
    }

    void showTask(AllTasks* tasks ) {
        tasks->showAll();
    }

    void clear() { //clear the terminal and move the cursor to the top left
        cout << "\033[2J\033[H";
    }

    void commandLine() {
        seperator();
        cout << "Your command: ";
    }
};
#endif //STAGE_H