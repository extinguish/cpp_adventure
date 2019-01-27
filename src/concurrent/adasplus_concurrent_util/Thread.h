//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_THREAD_H
#define CPPADVENTURE_THREAD_H

#include <stdint.h>

#include "log.h"
#include "Queue.h"
#include "CmdThread.h"

namespace adasplus {

    typedef struct Message {
        int32_t messageId;
        void *dataPtr;
        size_t dataLen;
    } Message;

    class Thread {
    public:
        Thread();

        virtual ~Thread();

        int32_t start();

        int32_t stop();

        int32_t processDataNotify(Message *message);

    protected:
        virtual int32_t processData(Message *message) = 0;

    private:
        static void *dataProcRoutine(void *data);

    private:
        QCameraQueue mDataQ;
        CmdThread mProcTh;

    };
}

#endif //CPPADVENTURE_THREAD_H
