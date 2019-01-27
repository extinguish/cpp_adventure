//
// Created by guoshichao on 19-1-24.
//

#include <stdlib.h>
#include <errno.h>

#include "Thread.h"

namespace adasplus {
    Thread::Thread() : mDataQ(NULL, NULL) {

    }

    Thread::~Thread() {

    }

    int32_t Thread::start() {
        int32_t rc = 0;
        mDataQ.init();
        rc = mProcTh.launch(dataProcRoutine, this);
        return rc;
    }

    int32_t Thread::stop() {
        int32_t rc = 0;
        rc = mProcTh.exit();
        return rc;
    }

    int32_t Thread::processDataNotify(Message *message) {
        LOGD("process data notify\n");
        mDataQ.enqueue(message);
        return mProcTh.sendCmd(CMD_TYPE_PROCESS, 0, 0);
    }

    void *Thread::dataProcRoutine(void *data) {
        LOGD("data procedure routine\n");
        int running = 1;
        int ret;
        Thread *thread = (Thread *) data;
        CmdThread *cmdThread = &thread->mProcTh;
        do {
            do {
                ret = sem_wait(&cmdThread->cmd_sem);
                if (ret != 0 && errno != EINVAL) {
                    return NULL;
                }
            } while (ret != 0);

            cmd_type_t cmd = cmdThread->getCmd();
            switch (cmd) {
                case CMD_TYPE_PROCESS: {
                    LOGD("receive command of %d\n", CMD_TYPE_PROCESS);
                    Message *message = (Message *) thread->mDataQ.dequeue();
                    LOGD("have get the message\n");
                    if (message != NULL) {
                        thread->processData(message);
                    }
                    break;
                }
                case CMD_TYPE_EXIT:
                    thread->mDataQ.flush();
                    running = 0;
                    break;
                default:
                    break;
            }
        } while (running);
        return NULL;
    }
}