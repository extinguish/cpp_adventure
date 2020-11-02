//
// Created by guoshichao on 19-12-30.
//

#include "Timers.h"

#include <limits.h>
#include <sys/time.h>
#include <time.h>

#if defined(HAVE_ANDROID_OS)
nsecs_t systemTime(int clock)
{
    static const clockid_t clocks[] = {
            CLOCK_REALTIME,
            CLOCK_MONOTONIC,
            CLOCK_PROCESS_CPUTIME_ID,
            CLOCK_THREAD_CPUTIME_ID,
            CLOCK_BOOTTIME
    };
    struct timespec t;
    t.tv_sec = t.tv_nsec = 0;
    clock_gettime(clocks[clock], &t);
    return nsecs_t(t.tv_sec)*1000000000LL + t.tv_nsec;
}
#else

nsecs_t systemTime(int /*clock*/) {
    // Clock support varies widely across hosts. Mac OS doesn't support
    // posix clocks, older glibcs don't support CLOCK_BOOTTIME and Windows
    // is windows.
    struct timeval t;
    t.tv_sec = t.tv_usec = 0;
    gettimeofday(&t, NULL);
    return nsecs_t(t.tv_sec) * 1000000000LL + nsecs_t(t.tv_usec) * 1000LL;
}

#endif

int toMillisecondTimeoutDelay(nsecs_t referenceTime, nsecs_t timeoutTime) {
    int timeoutDelayMillis;
    if (timeoutTime > referenceTime) {
        uint64_t timeoutDelay = uint64_t(timeoutTime - referenceTime);
        if (timeoutDelay > uint64_t((INT_MAX - 1) * 1000000LL)) {
            timeoutDelayMillis = -1;
        } else {
            timeoutDelayMillis = (timeoutDelay + 999999LL) / 1000000LL;
        }
    } else {
        timeoutDelayMillis = 0;
    }
    return timeoutDelayMillis;
}
