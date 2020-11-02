//
// Created by guoshichao on 2020/6/9.
//

#include <stdio.h>
#include "Manager.h"
#include "Child.h"
#include <unistd.h>

Manager *manager = new Manager();
Child *child = new Child(100);

int main(int argc, char **argv) {
    child->setCallback(manager);

    manager->addChild(child);

    child->run();

    usleep(1000 * 1000 * 1000);
}
