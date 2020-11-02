//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_THREADDEFS_H
#define CPPADVENTURE_THREADDEFS_H

// ---------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif

typedef void *android_thread_id_t;

typedef int (*android_thread_func_t)(void *);

#ifdef __cplusplus
} // extern "C"
#endif

namespace adasplus {
    // ---------------------------------------------------------------------------

    typedef android_thread_id_t thread_id_t;
    typedef android_thread_func_t thread_func_t;

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

#endif //CPPADVENTURE_THREADDEFS_H
