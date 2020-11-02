//
// Created by guoshichao on 19-1-27.
//

#include <iostream>

#include "Timers.h"
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;

int handleTimesUpAction(void *clientPtr) {
    cout << "Callback function --> times up, and do the right thing now " << endl;
    return 0;
}

int main(int argc, char **argv) {
    Timer timer;
    timer.create(0, 1000, []() { cout << "times up, and do something" << endl; });

    // timer.create(0, 1000, handleTimesUpAction);

    sleep(10000);
}