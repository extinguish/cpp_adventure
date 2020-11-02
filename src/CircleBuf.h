//
// Created by guoshichao on 19-8-1.
//

#ifndef CPPADVENTURE_CIRCLEBUF_H
#define CPPADVENTURE_CIRCLEBUF_H

#include <pthread.h>
#include <stddef.h>
#include <cstdint>

#include <stdio.h>

class CircleBuf {
public:
    CircleBuf(int size);

    ~CircleBuf();

public:
    void writeBuf(uint8_t *data, int len);

    int readBuf(uint8_t *data, int len);


    int getReadPtr();

    int getWritePtr();

private:
    pthread_mutex_t mMutex;
    int mTotalSize;
    int mReadPtr;
    int mWritePtr;
    uint8_t *mCircleBuf;


};


#endif //CPPADVENTURE_CIRCLEBUF_H
