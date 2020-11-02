//
// Created by guoshichao on 19-7-19.
//

#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <cstdio>

typedef int64_t time64_t;

time64_t now() {
    time64_t v;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    v = tv.tv_sec;
    v *= 1000;
    v += tv.tv_usec / 1000;
    return v;
}

typedef unsigned char BYTE;

int main(int argc, char **argv) {

    BYTE timeStamp[8];

    time64_t current = now();
    memcpy(timeStamp, &current, sizeof(time64_t));

    printf("the time are %d, %02x \n", current);
    for (int i = 0; i < 8; ++i) {
        printf("%02x ", timeStamp[i]);
    }

    printf("\n");

    unsigned int val = 455;
    unsigned char test = val;
    printf("test value are %d\n", test);


}

