//
// Created by guoshichao on 2020/6/29.
//

#ifndef CPPADVENTURE_JT1078CIRCLEBUFFER_H
#define CPPADVENTURE_JT1078CIRCLEBUFFER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <pthread.h>

namespace adasplus {

    // in JT1078 protocol, the media packet are started with 0x30316364, but as our device is little-endian
    // so the need to convert the endian before we use it
    const static unsigned int JT1078_MEDIA_PACKET_START_IDENTIFIER = 0x64633130;

    /**
     * The main implementation are cloned from Circle808ClientBuffer, but process message that starts with 0x30316364
     */
    class Circle1078ClientBuffer {
    public:
        explicit Circle1078ClientBuffer(size_t size);

        ~Circle1078ClientBuffer();

        void write(const void *data, size_t size);

        void findMessage();

    private:
        void findOneMessage(int *index, int *begin, size_t *messageSize);

    public:
        void getMessage(void *msg, size_t msgLen);

    private:
        uint8_t *mPtr;
        size_t mTotalSize;

        off_t mReadPtr;
        off_t mWritePtr;
        pthread_mutex_t mMutex;
    };
}


#endif //CPPADVENTURE_JT1078CIRCLEBUFFER_H
