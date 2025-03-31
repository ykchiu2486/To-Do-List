//TODO
#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include "improvedTask.h"
#include "Date.h"
#include "FileIO.h"
using std::cout;

void seperator() {
    cout << "-------------------------------------------------------------------\n";
}

class Banner {
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

public:
    void show() {
        bigTitle();
        seperator();
        cout << "Now time: ";
        nowDate();
        cout << "\n";
        seperator();
    }
};

class Stage {
public:
    void init() {
        Banner* banner = new Banner;
        banner->show();
        delete banner;
    }

    void showTask(AllTasks* tasks ) {
        tasks->showAll();
    }

    void clear() {
        cout << "\033[2J\033[H";
    }
};
#endif //STAGE_H