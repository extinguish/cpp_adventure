//
// Created by guoshichao on 2020/6/9.
//

#include "Child.h"
#include <unistd.h>
#include <cstdio>

Child::Child(int childId) : childId(childId) {

}

Child::~Child() {

}

int Child::getChildId() {
    return childId;
}

void Child::setCallback(Callback *callback) {
    this->callback = callback;
}

void Child::run() {
    for (int i = 0; i < 10; ++i) {
        usleep(1000 * 1000);
        printf("processing [%d]\n", i);
    }
    callback->delSelf(childId);
}


