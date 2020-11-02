//
// Created by guoshichao on 2020/6/9.
//

#ifndef CPPADVENTURE_CHILD_H
#define CPPADVENTURE_CHILD_H

#include "Callback.h"

class Child {
public:
    Child(int childId);

    ~Child();

public:
    int getChildId();

    void setCallback(Callback *callback);

    void run();
private:
    Callback *callback;

private:
    int childId;


};


#endif //CPPADVENTURE_CHILD_H
