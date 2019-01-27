//
// Created by guoshichao on 19-1-27.
//

#ifndef CPPADVENTURE_EPOLL_H
#define CPPADVENTURE_EPOLL_H

#include <sys/epoll.h>

namespace adasplus {

    class IEpollEventListener {
    public:
        virtual void onEpollEvent(int fd, uint32_t event) = 0;
    };

    class Epoll {
    public:
        Epoll(int maxepollsize, int timeout);

        ~Epoll();

        void eventLoop();

        void addEvent(int fd, uint32_t event);

        void updateEvent(int fd, uint32_t event);

        void deleteEvent(int fd, uint32_t event);

        void setEpollEventListener(IEpollEventListener *listener) { mEpollEventListener = listener; }

        void setLoop(bool loop) { mLoop = loop; }

    private:
        bool mLoop;
        IEpollEventListener *mEpollEventListener;
        int mTimeOut;
        int mMaxEpollSize;
        int mEpollfd;
    };
}


#endif //CPPADVENTURE_EPOLL_H
