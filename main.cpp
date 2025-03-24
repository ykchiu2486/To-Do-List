#include "basicTask.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    string n = "name";
    string c = "category";
    Basic_task a(n, c, false);
    a.show();
}