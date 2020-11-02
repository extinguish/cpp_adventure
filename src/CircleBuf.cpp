//
// Created by guoshichao on 19-8-1.
//

#include <cstring>
#include "CircleBuf.h"

CircleBuf::CircleBuf(int size) :
        mTotalSize(size),
        mWritePtr(0),
        mReadPtr(0) {
    pthread_mutex_init(&mMutex, NULL);
    mCircleBuf = new uint8_t[size];
}

CircleBuf::~CircleBuf() {
    pthread_mutex_destroy(&mMutex);
    delete[] mCircleBuf;

}

int CircleBuf::getReadPtr() {
    return mReadPtr;
}

int CircleBuf::getWritePtr() {
    return mWritePtr;
}

void CircleBuf::writeBuf(uint8_t *data, int len) {
    pthread_mutex_lock(&mMutex);
    if (len < 0) {
        printf("the length %d are invalid\n", len);
        return;
    }

    if (mWritePtr + len <= mTotalSize) {
        memcpy(mCircleBuf + mWritePtr, data, len);
        mWritePtr += len;
    } else {
        int left = mTotalSize - mWritePtr;
        memcpy(mCircleBuf + mWritePtr, data, left);
        memcpy(mCircleBuf, data + left, len - left);
        mWritePtr = len - left;
    }
    pthread_mutex_unlock(&mMutex);
}

/**
 * read data from circle buffer
 *
 * @param data the container using to store the data that we read from mCircieBuf
 * @param len the length we want to read from mCircleBuf
 * @return the true length of data that we read from mCircleBuf
 *         returns -1 if the mCircleBuf is unavailable
 */
int CircleBuf::readBuf(uint8_t *data, int len) {
    pthread_mutex_lock(&mMutex);
    if (mReadPtr == mWritePtr || mTotalSize == 0 || len < 0) {
        pthread_mutex_unlock(&mMutex);
        return -1;
    } else {
        if (mReadPtr + len <= mWritePtr) {
            memcpy(data, mCircleBuf + mReadPtr, len);
            mReadPtr += len;
            pthread_mutex_unlock(&mMutex);
            return len;
        } else if (mReadPtr + len > mWritePtr) {
            if (mReadPtr <= mWritePtr) {
                pthread_mutex_unlock(&mMutex);
                return -1;
            } else if (mReadPtr > mWritePtr) {
                if (mReadPtr + len <= mTotalSize) {
                    memcpy(data, mCircleBuf + mReadPtr, len);
                    mReadPtr += len;
                    pthread_mutex_unlock(&mMutex);
                    return len;
                } else if (mReadPtr + len > mTotalSize) {
                    int left = mTotalSize - mReadPtr;
                    memcpy(data, mCircleBuf + mReadPtr, left);
                    int begin = len - (mTotalSize - mReadPtr);
                    if (begin <= mWritePtr) {
                        memcpy(data + left, mCircleBuf, begin);
                        mReadPtr = begin;
                        pthread_mutex_unlock(&mMutex);
                        return len;
                    } else {
                        pthread_mutex_unlock(&mMutex);
                        return -1;
                    }
                }
            }

        }
    }
    pthread_mutex_unlock(&mMutex);
    return -1;
}

