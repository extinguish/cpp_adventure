//
// Created by guoshichao on 19-2-14.
//

#ifndef CPPADVENTURE_APPLE_H
#define CPPADVENTURE_APPLE_H

#include <string.h>
#include <stdio.h>

#include "../RefBase.h"
#include "../log.h"

// Test the shared pointer feature
using namespace android;

class Apple : public RefBase {
public:
    Apple(const char *name) {
        strcpy(appleName, name);
        ALOG("the length of the appleName are %zu \n", strlen(appleName));
        ALOG("construct %s \n", name);
    }

    ~Apple() {
        ALOG("destruct the %s\n", appleName);
    }

    void foo() {
        ALOG("we are working under Apple instance \n");
    }

private :
    char appleName[64];
};


#endif //CPPADVENTURE_APPLE_H
