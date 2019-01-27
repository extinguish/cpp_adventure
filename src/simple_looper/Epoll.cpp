//
// Created by guoshichao on 19-1-27.
//
#include "Epoll.h"

#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

namespace adasplus {
    Epoll::Epoll(int maxepollsize, int timeout) : mMaxEpollSize(maxepollsize),
                                                  mTimeOut(timeout),
                                                  mLoop(false),
                                                  mEpollEventListener(NULL) {
        mEpollfd = epoll_create(maxepollsize);
    }

    Epoll::~Epoll() {
        close(mEpollfd);
    }

    void Epoll::eventLoop() {
        struct epoll_event events[mMaxEpollSize];
        int ret, i;
        mLoop = true;
        for (;;) {
            if (!mLoop) {
                break;
            }
            /** Wait for events on an epoll instance "mEpollfd". Returns the number of
            triggered events returned in "events" buffer. Or -1 in case of
            error with the "errno" variable set to the specific error code. The
            "events" parameter is a buffer that will contain triggered
            events. The "mMaxEpollSize" is the maximum number of events to be
            returned ( usually size of "events" ). The "timeout" parameter
            specifies the maximum wait time in milliseconds (-1 == infinite).

            This function is a cancellation point and therefore not marked with
            __THROW.  */
            ret = epoll_wait(mEpollfd, events, mMaxEpollSize, mTimeOut);
            if (ret == -1) {//ERROR
                if (errno == EINTR) { // Interrupted system call
                    std::cout << "the epoll action are interrupted by system" << std::endl;
                    continue;
                } else {
                    std::cout << "the error are " << strerror(errno) << "and need break the loop" << std::endl;
                    break;
                }
            } else if (ret == 0) {//TIMEOUT
                std::cout << "the event are timeout, and we need to wait for another loop" << std::endl;
                continue;
            } else {//NORMAL
                std::cout << "the event we cared are finally happen" << std::endl;
                for (i = 0; i < ret; i++) {
                    if (mEpollEventListener != NULL) {
                        mEpollEventListener->onEpollEvent(events[i].data.fd, events[i].events);
                    }
                }
            }
        }
    }

    void Epoll::addEvent(int fd, uint32_t event) {
        struct epoll_event ev;
        ev.data.fd = fd; /* User data variable */
        ev.events = event; /* Epoll events */
        /** Manipulate an epoll instance "mEpollfd".
         * Returns 0 in case of success, -1 in case of error ( the "errno" variable will contain the
        specific error code ) The "op" parameter is one of the EPOLL_CTL_*
        constants defined above. The "fd" parameter is the target of the
        operation. The "event" parameter describes which events the caller
        is interested in and any associated user data.  */
        epoll_ctl(mEpollfd, EPOLL_CTL_ADD, fd, &ev);
    }

    void Epoll::updateEvent(int fd, uint32_t event) {
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = event;
        epoll_ctl(mEpollfd, EPOLL_CTL_MOD, fd, &ev);
    }

    void Epoll::deleteEvent(int fd, uint32_t event) {
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = event;
        epoll_ctl(mEpollfd, EPOLL_CTL_DEL, fd, &ev);
    }
}

