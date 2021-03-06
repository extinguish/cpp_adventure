//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_THREAD_H
#define CPPADVENTURE_THREAD_H

#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#include <pthread.h>

#include "Condition.h"
#include "Errors.h"
#include "Mutex.h"
#include "Timers.h"
#include "ThreadDefs.h"

namespace adasplus {
    class Thread {
    public:
        Thread(bool canCallJava = true);

        virtual ~Thread();

        // Start the thread in threadLoop() which needs to be implemented.
        virtual status_t run(const char *name = 0,
                             int32_t priority = PRIORITY_DEFAULT,
                             size_t stack = 0);

        // Ask this object's thread to exit. This function is asynchronous, when the
        // function returns the thread might still be running. Of course, this
        // function can be called from a different thread.
        virtual void requestExit();

        // Good place to do one-time initializations
        virtual status_t readyToRun();

        // Call requestExit() and wait until this object's thread exits.
        // BE VERY CAREFUL of deadlocks. In particular, it would be silly to call
        // this function from this object's thread. Will return WOULD_BLOCK in
        // that case.
        status_t requestExitAndWait();

        // Wait until this object's thread exits. Returns immediately if not yet running.
        // Do not call from this object's thread; will return WOULD_BLOCK in that case.
        status_t join();

        // Indicates whether this thread is running or not.
        bool isRunning() const;

#ifdef HAVE_ANDROID_OS
        // Return the thread's kernel ID, same as the thread itself calling gettid(),
    // or -1 if the thread is not running.
            pid_t       getTid() const;
#endif

    protected:
        // exitPending() returns true if requestExit() has been called.
        bool exitPending() const;

    private:
        // Derived class must implement threadLoop(). The thread starts its life
        // here. There are two ways of using the Thread object:
        // 1) loop: if threadLoop() returns true, it will be called again if
        //          requestExit() wasn't called.
        // 2) once: if threadLoop() returns false, the thread will exit upon return.
        virtual bool threadLoop() = 0;

    private:
        Thread &operator=(const Thread &);

        static int _threadLoop(void *user);

        const bool mCanCallJava;
        // always hold mLock when reading or writing
        thread_id_t mThread;
        mutable Mutex mLock;
        Condition mThreadExitedCondition;
        status_t mStatus;
        // note that all accesses of mExitPending and mRunning need to hold mLock
        volatile bool mExitPending;
        volatile bool mRunning;
        Thread *mHoldSelf;
#ifdef HAVE_ANDROID_OS
        // legacy for debugging, not used by getTid() as it is set by the child thread
    // and so is not initialized until the child reaches that point
            pid_t           mTid;
#endif

    };
}


#endif //CPPADVENTURE_THREAD_H
