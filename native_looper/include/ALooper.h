//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_ALOOPER_H
#define CPPADVENTURE_ALOOPER_H

#include <stdint.h>
#include "Errors.h"
#include "Mutex.h"
#include "Condition.h"
#include "AString.h"
#include <list>
#include "ABase.h"
#include "Thread.h"

namespace adasplus {

    enum {
        /*
         * ***********************************************
         * ** Keep in sync with android.os.Process.java **
         * ***********************************************
         *
         * This maps directly to the "nice" priorities we use in Android.
         * A thread priority should be chosen inverse-proportionally to
         * the amount of work the thread is expected to do. The more work
         * a thread will do, the less favorable priority it should get so that
         * it doesn't starve the system. Threads not behaving properly might
         * be "punished" by the kernel.
         * Use the levels below when appropriate. Intermediate values are
         * acceptable, preferably use the {MORE|LESS}_FAVORABLE constants below.
         */
                ANDROID_PRIORITY_LOWEST = 19,
        /* use for background tasks */
                ANDROID_PRIORITY_BACKGROUND = 10,
        /* most threads run at normal priority */
                ANDROID_PRIORITY_NORMAL = 0,
        /* threads currently running a UI that the user is interacting with */
                ANDROID_PRIORITY_FOREGROUND = -2,
        /* the main UI thread has a slightly more favorable priority */
                ANDROID_PRIORITY_DISPLAY = -4,
        /* ui service treads might want to run at a urgent display (uncommon) */
                ANDROID_PRIORITY_URGENT_DISPLAY = -8,
        /* all normal audio threads */
                ANDROID_PRIORITY_AUDIO = -16,
        /* service audio threads (uncommon) */
                ANDROID_PRIORITY_URGENT_AUDIO = -19,
        /* should never be used in practice. regular process might not
         * be allowed to use this level */
                ANDROID_PRIORITY_HIGHEST = -20,
        ANDROID_PRIORITY_DEFAULT = ANDROID_PRIORITY_NORMAL,
        ANDROID_PRIORITY_MORE_FAVORABLE = -1,
        ANDROID_PRIORITY_LESS_FAVORABLE = +1,
    };

    enum {
        PRIORITY_LOWEST = ANDROID_PRIORITY_LOWEST,
        PRIORITY_BACKGROUND = ANDROID_PRIORITY_BACKGROUND,
        PRIORITY_NORMAL = ANDROID_PRIORITY_NORMAL,
        PRIORITY_FOREGROUND = ANDROID_PRIORITY_FOREGROUND,
        PRIORITY_DISPLAY = ANDROID_PRIORITY_DISPLAY,
        PRIORITY_URGENT_DISPLAY = ANDROID_PRIORITY_URGENT_DISPLAY,
        PRIORITY_AUDIO = ANDROID_PRIORITY_AUDIO,
        PRIORITY_URGENT_AUDIO = ANDROID_PRIORITY_URGENT_AUDIO,
        PRIORITY_HIGHEST = ANDROID_PRIORITY_HIGHEST,
        PRIORITY_DEFAULT = ANDROID_PRIORITY_DEFAULT,
        PRIORITY_MORE_FAVORABLE = ANDROID_PRIORITY_MORE_FAVORABLE,
        PRIORITY_LESS_FAVORABLE = ANDROID_PRIORITY_LESS_FAVORABLE,
    };

}

namespace adasplus {
    struct AMessage;
    struct AHandler;

    struct ALooper {
        typedef int32_t event_id;
        typedef int32_t handler_id;

        ALooper();

        void setName(const char *name);

        handler_id registerHandler(const AHandler *handler);

        void unregisterHandler(handler_id handlerID);

        status_t start(bool runOnCallingThread = false,
                       bool canCallJava = false, int32_t priority = PRIORITY_DEFAULT);

        status_t stop();

        static int64_t getNowUs();

    protected:
        virtual ~ALooper();

    private:
        friend struct ALooperRoster;
        struct Event {
            int64_t mWhenUs;
            AMessage *mMessage;
        };

        Mutex mLock;
        Condition mQueuedChangedCondition;

        AString mName;

        std::list<Event> mEventQueue;

        struct LooperThread;
        LooperThread *mThread;

        bool mRunningLocally;

        void post(const AMessage *message, int64_t delayUs);

        bool loop();

        DISALLOW_EVIL_CONSTRUCTORS(ALooper);
    };
}

#endif //CPPADVENTURE_ALOOPER_H
