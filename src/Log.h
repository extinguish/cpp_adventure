//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_LOG_H
#define CPPADVENTURE_LOG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#define ENABLE_LOG 1

#define LOGD(...) if(ENABLE_LOG) printf(__VA_ARGS__)

#ifdef __cplusplus
};
#endif

#endif //CPPADVENTURE_LOG_H
