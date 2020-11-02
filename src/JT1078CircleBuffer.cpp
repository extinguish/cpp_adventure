//
// Created by guoshichao on 2020/6/29.
//

#include "JT1078CircleBuffer.h"
#include <unistd.h>
#include <fcntl.h>

adasplus::Circle1078ClientBuffer::Circle1078ClientBuffer(size_t size) : mPtr(nullptr),
                                                                        mTotalSize(size),
                                                                        mReadPtr(0),
                                                                        mWritePtr(0) {
    pthread_mutex_init(&mMutex, nullptr);
    mPtr = (uint8_t *) malloc(size);
    if (mPtr != nullptr) {
        memset(mPtr, 0, size);
    }
}

adasplus::Circle1078ClientBuffer::~Circle1078ClientBuffer() {
    if (mPtr != NULL) {
        free(mPtr);
        mPtr = NULL;
    }
    pthread_mutex_destroy(&mMutex);
}

void adasplus::Circle1078ClientBuffer::write(const void *data, size_t size) {
    pthread_mutex_lock(&mMutex);
    if (mWritePtr + size <= mTotalSize) {
        memcpy(mPtr + mWritePtr, data, size);
        mWritePtr += size;
    } else {
        // exceed the ring buffer, we need to overflow the buffer from start again
        size_t left = mTotalSize - mWritePtr;
        memcpy(mPtr + mWritePtr, data, left);
        memcpy(mPtr, (uint8_t *) data + left, size - left);
        mWritePtr = size - left;
    }
    pthread_mutex_unlock(&mMutex);

    printf("find 1078 Message\n");
    findMessage();
    printf("find 1078 Message over!\n");
}

void adasplus::Circle1078ClientBuffer::findMessage() {
    pthread_mutex_lock(&mMutex);
    int index = mReadPtr;
    size_t messageSize = 0;
    int begin = mReadPtr;
    if (mReadPtr <= mWritePtr) {
        for (index = mReadPtr; index < mWritePtr; index++) {
            if (mPtr[index] == 0x30 && mPtr[index + 1] == 0x31 && mPtr[index + 2] == 0x63 && mPtr[index + 3] == 0x64) {
                printf("meet -------------> %.8x \n", JT1078_MEDIA_PACKET_START_IDENTIFIER);
                findOneMessage(&index, &begin, &messageSize);
            }
        }
    } else {
        while (index <= mTotalSize) {
            if (mPtr[index] == 0x30 && mPtr[index + 1] == 0x31 && mPtr[index + 2] == 0x63 && mPtr[index + 3] == 0x64) {
                printf("meet ------------> %.8x while (index <= mTotalSize)\n", JT1078_MEDIA_PACKET_START_IDENTIFIER);
                findOneMessage(&index, &begin, &messageSize);
            }
            index++;
        }
        begin = mReadPtr;
        int left = mTotalSize - begin;
        if (left == 0) {
            begin = 0;
        }
        index = 0;
        while (index < mWritePtr) {
            if (mPtr[index] == 0x30 && mPtr[index + 1] == 0x31 && mPtr[index + 2] == 0x63 && mPtr[index + 3] == 0x64) {
                if (left != 0) {
                    messageSize = left + index;
                    uint8_t tmp[messageSize];
                    memset(tmp, 0, messageSize);
                    memcpy(tmp, mPtr + begin, left);
                    memcpy(tmp + left, mPtr, index);

                    printf("---[");
                    for (int i = 0; i < messageSize; i++) {
                        printf("%02x ", tmp[i]);
                    }
                    printf("]\n");
                    left = 0;

                    getMessage(tmp, messageSize);

                    mReadPtr = index + 1;
                    begin = mReadPtr;
                } else {
                    printf("---------------------------> \n");
                    findOneMessage(&index, &begin, &messageSize);
                }
            }
            index++;
        }
    }
    pthread_mutex_unlock(&mMutex);
}

void adasplus::Circle1078ClientBuffer::findOneMessage(int *index, int *begin, size_t *messageSize) {
    // when we meet the first 0x30316364, the findOneMessage() will return immediately, as the
    // *index are equals with *begin, so the value of *messageSize are equals to 0,
    // and this method will return immediately
    // when we meet the second 0x30316364, this indicates that we meet the new rtp message,
    // and the *messageSize will be > 0
    // but as the this second 0x30316364 belongs to the new rtp message, so the actual value
    // of *messageSize should be (*index - *begin), do not take the 0x30 into the previous rtp message
    *messageSize = *index - *begin;
    if (*messageSize > 0) {
        printf("[");
        unsigned char *ptr = mPtr + *begin;
        for (int i = 0; i < *messageSize; i++) {
            printf("%02x ", ptr[i]);
        }
        printf("]\n");

        getMessage(mPtr + *begin, *messageSize);
        mReadPtr = *index;
    }
    *begin = *index;
}

int testFd = -1;
void adasplus::Circle1078ClientBuffer::getMessage(void *msg, size_t msgLen) {
    // write the message to the test file, and compare the difference
    if (testFd == -1) {
        const char *testDataFilePath = "/media/guoshichao/04167E5E167E50A2/a_scguo_cache/06_30/jt1078_received1.bin";
        testFd = open(testDataFilePath, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0644);
    }
    ::write(testFd, msg, msgLen);
}

#define READ_BUF (1024 * 1024)

int main(int argc, char **argv) {
    adasplus::Circle1078ClientBuffer *buffer = new adasplus::Circle1078ClientBuffer(1024 * 1024);

    const char *testDataFilePath = "/media/guoshichao/04167E5E167E50A2/a_scguo_cache/06_29/jt1078_received.bin";
    int fd = open(testDataFilePath, O_RDONLY);
    int readCount = 0;
    uint8_t readBuf[READ_BUF] = {0};

    while ((readCount = read(fd, readBuf, READ_BUF)) > 0) {
        buffer->write(readBuf, readCount);
    }
}
