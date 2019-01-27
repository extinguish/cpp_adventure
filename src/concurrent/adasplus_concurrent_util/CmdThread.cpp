//
// Created by guoshichao on 19-1-24.
//
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>

#include "CmdThread.h"
#include "log.h"

CmdThread::CmdThread() : cmd_queue() {
    cmd_pid = 0;
    sem_init(&sync_sem, 0);
    sem_init(&cmd_sem, 0);
}

CmdThread::~CmdThread() {
    sem_destroy(&sync_sem);
    sem_destroy(&cmd_sem);
}

int32_t CmdThread::launch(void *(*start_routine)(void *),
                          void *user_data) {
    pthread_create(&cmd_pid, NULL, start_routine, user_data);
    return 1;
}

int32_t CmdThread::setName(const char *name) {
    prctl(PR_SET_NAME, (unsigned long) name, 0, 0);
    return 1;
}

int32_t CmdThread::sendCmd(cmd_type_t cmd, uint8_t sync_cmd, uint8_t priority) {
    cmd_t *node = (cmd_t *) malloc(sizeof(cmd_t));

    memset(node, 0, sizeof(cmd_t));
    node->cmd = cmd;
    if (priority) {
        LOGD("enqueue data with priority\n");
        cmd_queue.enqueueWithPriority((void *) node);
    } else {
        LOGD("enqueue data without priority\n");
        cmd_queue.enqueue((void *) node);
    }

    sem_post(&cmd_sem);
    if (sync_cmd) {
        LOGD("wait on semaphore\n");
        sem_wait(&sync_sem);
    }
    return 1;
}

cmd_type_t CmdThread::getCmd() {
    cmd_type_t cmd = CMD_TYPE_NONE;
    cmd_t *node = (cmd_t *) cmd_queue.dequeue();
    if (NULL == node) {
        return CMD_TYPE_NONE;
    } else {
        cmd = node->cmd;
        free(node);
    }

    return cmd;
}

int32_t CmdThread::exit() {
    int32_t rc = 1;
    if (cmd_pid == 0) {
        return 1;
    }

    rc = sendCmd(CMD_TYPE_EXIT, 0, 1);
    if (rc != 1) {
        return rc;
    }

    if (pthread_join(cmd_pid, NULL) != 0) {

    }
    cmd_pid = 0;
    return rc;
}
