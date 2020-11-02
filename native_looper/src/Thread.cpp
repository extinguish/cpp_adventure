//
// Created by guoshichao on 19-12-30.
//

// the header file of std-c99
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// the header file of POSIX
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>

// the header file of linux
#include <sys/prctl.h>

#include "Thread.h"

#include <sys/syscall.h>

#define gettid() syscall(__NR_gettid)

using namespace adasplus;

/*
 * Create and run a new thread.
 *
 * We create it "detached", so it cleans up after itself.
 */

typedef void *(*android_pthread_entry)(void *);

struct thread_data_t {
    thread_func_t entryFunction;
    void *userData;
    int priority;
    char *threadName;

    // we use this trampoline when we need to set the priority with
    // nice/setpriority, and name with prctl.
    static int trampoline(const thread_data_t *t) {
        thread_func_t f = t->entryFunction;
        void *u = t->userData;
        int prio = t->priority;
        char *name = t->threadName;
        delete t;
        setpriority(PRIO_PROCESS, 0, prio);
        if (prio >= ANDROID_PRIORITY_BACKGROUND) {
            set_sched_policy(0, SP_BACKGROUND);
        } else {
            set_sched_policy(0, SP_FOREGROUND);
        }

        if (name) {
            androidSetThreadName(name);
            free(name);
        }
        return f(u);
    }
};








