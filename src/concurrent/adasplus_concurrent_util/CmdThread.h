//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_CMDTHREAD_H
#define CPPADVENTURE_CMDTHREAD_H

#include <pthread.h>
#include <stdint.h>
#include "Queue.h"
#include "sem.h"

typedef enum {
    CMD_TYPE_NONE,
    CMD_TYPE_PROCESS,
    CMD_TYPE_EXIT,
} cmd_type_t;

typedef struct {
    cmd_type_t cmd;
} cmd_t;

class CmdThread {
public:
    CmdThread();

    ~CmdThread();

    int32_t launch(void *(*start_routine)(void *),
                   void *user_data);

    int32_t setName(const char *name);

    int32_t exit();

    int32_t sendCmd(cmd_type_t cmd, uint8_t sync_cmd, uint8_t priority);

    cmd_type_t getCmd();

    QCameraQueue cmd_queue;
    pthread_t cmd_pid;
    util::semaphore_t cmd_sem;
    util::semaphore_t sync_sem;
};


#endif //CPPADVENTURE_CMDTHREAD_H
