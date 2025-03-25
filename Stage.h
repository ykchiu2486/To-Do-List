//TODO
#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include "improvedTask.h"
#include "Date.h"
#include "FileIO.h"
using std::cout;

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

    void seperator() {
        cout << "-------------------------------------------------------------------\n";
    }

    void nowDate() {
        Date now;
        now.show();
    }

public:
    void show() {
        bigTitle();
        seperator();
        cout << "Now time: ";
        nowDate();
        seperator();
    }
};

class Stage {
private:

public:
    void init() {
        Banner banner;
        banner.show();
    }

    void clear() {
        cout << "\033[2J\033[H";
    }
};
#endif //STAGE_H