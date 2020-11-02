//
// Created by guoshichao on 2020/6/9.
//

#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager() {

}

void Manager::delSelf(int childId) {
    for (std::list<Child *>::iterator iter = mChildList.begin();
         iter != mChildList.end();) {
        Child *child = *iter;
        if (child->getChildId() == childId) {
            delete child;
        }
    }
}

void Manager::addChild(Child *child) {
    mChildList.push_back(child);
}
