#include "improvedTask.h"
#include "Stage.h"
#include <iostream>
#include "FileIO.h"
#include <vector>
using namespace std;

AllTasks* read() {
    Reader* reader = new Reader("tasks.txt");
    AllTasks* alltasks = new AllTasks(reader->read());
    delete reader;
    return alltasks;
}

void write(AllTasks* alltasks) {
    Writer* writer = new Writer("tasks.txt");
    writer->write(alltasks->insideData());
    delete writer;
}

void init(Stage* stage, AllTasks* alltasks) {
    stage->banner();
    stage->showTask(alltasks);
    stage->commandLine();
}

int main() {
    AllTasks* alltasks = read();
    Stage* stage = new Stage;
    
    while(true) {
        init(stage, alltasks);
        string* testcommand = new string;
        cin >> *testcommand;
        
        if(*testcommand == "add") {
            stage->clear();
            stage->banner();
            MoreTask* nt = new MoreTask;
            nt->makeNew();
            alltasks->add(nt);
            alltasks->sort();
            stage->clear();
        }
        else if(*testcommand == "mod") {
            int* index = new int;
            cin >> *index;
            stage->clear();
            stage->banner();
            (*alltasks)[*index]->modify();
            stage->clear();
            alltasks->sort();
            delete index;
        }
        else if(*testcommand == "rm") {
            int* index = new int;
            cin >> *index;
            alltasks->deleteTask(*index);
            stage->clear();
            alltasks->sort();
            delete index;
        }
        else if(*testcommand == "show") {
            int* index = new int;
            cin >> *index;
            stage->clear();
            stage->banner();
            (*alltasks)[*index]->showThisTask();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            stage->clear();
            delete index;
        }
        else if(*testcommand == "filter") {
            stage->clear();
            stage->banner();
            alltasks->showByFilter();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            stage->clear();
        }
        else if(*testcommand == "exit") {
            write(alltasks);
            delete testcommand;
            break;
        }
        else {
            stage->clear();
        }
        
        delete testcommand;
    }
    
    delete stage;
    delete alltasks;
    
    return 0;
}