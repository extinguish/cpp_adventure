//
// Created by guoshichao on 2020/6/9.
//

#ifndef CPPADVENTURE_MANAGER_H
#define CPPADVENTURE_MANAGER_H

#include <list>

#include "Child.h"

class Manager : public Callback {
public:
    Manager();

    ~Manager();

public:
    void delSelf(int childId) override;

    void addChild(Child *child);

private:
    std::list<Child *> mChildList;
};


#endif //CPPADVENTURE_MANAGER_H
