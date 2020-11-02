//
// Created by guoshichao on 19-4-13.
//

/// like the TimeoutHandler.cpp, implement the timeout handler function
/// but this way is implemented by Linux signal mechanism


#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define RETRY_COUNT 4

#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR1

typedef void (*TimerHandler)(sigval_t signum);

class TimerTimeoutHandler {
public:
    virtual void handlerFunction() = 0;
};

class Timer {
public:
    Timer(TimerTimeoutHandler *timeHandler);

    ~Timer();

    void setDuration(long int seconds);

    void start();

    void restart();

    void timeout();

    void stop();

    void callbackWrapper();

    static void timeOutHandler(sigval_t This);

private:
    void createTimer(timer_t *timerid, TimerHandler handler_cb);

    void startTimer(timer_t timerid, int startTimeout, int cyclicTimeout);

    void stopTimer(timer_t timerid);

    void removeTimer(timer_t timerId);

    long int m_Duration;
    TimerTimeoutHandler *timeOutHandlerImp;
    timer_t timerid;
    int retryCount = 0;
};

class TimeTimeoutHandlerImp : public TimerTimeoutHandler {
public:
    TimeTimeoutHandlerImp() {}

    ~TimeTimeoutHandlerImp() {}

    // implemented from TimerTimeoutHandler
    void handlerFunction();
};


Timer::Timer(TimerTimeoutHandler *timeHandler) {
    timeOutHandlerImp = timeHandler;
    m_Duration = 0;

    TimerHandler handler_cb = &timeOutHandler;
    createTimer(&timerid, handler_cb);
}

Timer::~Timer() {
    stopTimer(timerid);
}

void Timer::setDuration(long int seconds) {
    m_Duration = seconds;
}

void Timer::start() {
    startTimer(timerid, m_Duration, 3);
}

void Timer::restart() {
    stopTimer(timerid);
    startTimer(timerid, m_Duration, 0);
}

void Timer::stop() {
    stopTimer(timerid);
}

void Timer::createTimer(timer_t *timerid, TimerHandler handler_cb) {
    sigevent sev;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    sched_param parm;

    parm.sched_priority = 255;
    pthread_attr_setschedparam(&attr, &parm);

    sev.sigev_notify_attributes = &attr;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = handler_cb;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCKID, &sev, timerid);
}

void Timer::startTimer(timer_t timerid, int startTimeout, int cyclicTimeout) {
    itimerspec its;

    /* Start the timer */
    its.it_value.tv_sec = startTimeout;
    its.it_value.tv_nsec = 0;

    /* for cyclic timer */
    its.it_interval.tv_sec = cyclicTimeout;
    its.it_interval.tv_nsec = 0;

    timer_settime(timerid, 0, &its, NULL);
}

void Timer::stopTimer(timer_t timerid) {
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime(timerid, 0, &its, NULL);
}

void Timer::timeOutHandler(sigval_t This) {
    Timer *timer = (Timer *) This.sival_ptr;
    timer->callbackWrapper();
}

void Timer::callbackWrapper() {
    timeOutHandlerImp->handlerFunction();
    stopTimer(timerid);
}

void Timer::removeTimer(timer_t timerId) {
    timer_delete(timerId);
}

void TimeTimeoutHandlerImp::handlerFunction() {
    cout << "timeout" << endl;

}

int main(int argc, char **argv) {

    TimerTimeoutHandler *timeoutHandler = new TimeTimeoutHandlerImp();
    Timer *timer = new Timer(timeoutHandler);
    timer->setDuration(3);
    timer->start();
    timer->stop();
    sleep(100);

    return 0;
}


