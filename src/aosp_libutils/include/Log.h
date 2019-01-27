// DO NOT INCLUDE ANYTHING NEW IN THIS FILE.

// <log/log.h> has replaced this file and all changes should go there instead.
// This path remains strictly to include that header as there are thousands of
// references to <utils/Log.h> in the tree.

#ifndef CPPADVENTURE_LOG_H
#define CPPADVENTURE_LOG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#define ENABLE_LOG 1


#define LOGD(...) if(ENABLE_LOG) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)

#ifdef __cplusplus
};
#endif

#endif