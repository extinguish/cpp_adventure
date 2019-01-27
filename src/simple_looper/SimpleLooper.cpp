//
// Created by guoshichao on 19-1-27.
//

#include "Epoll.h"
#include <iostream>

using adasplus::Epoll;

using std::cin;
using std::cout;
using std::endl;

class UploadLocalData : public adasplus::IEpollEventListener {
public:
    void onEpollEvent(int fd, uint32_t event);
};

void UploadLocalData::onEpollEvent(int fd, uint32_t event) {
    cout << "on fd of " << fd << "happened, and the event are " << event << endl;
}


// create a simple infinite looper function
int main(int argc, char **argv) {
    const int maxPollSize = 2;
    const int timeout = -1; // -1 indicates infinite loop
    Epoll epoll{maxPollSize, 300};

    const int uploadLocalDataFd = 100;
    const uint32_t uploadLocalDataEvent = 200;

    epoll.addEvent(uploadLocalDataFd, uploadLocalDataEvent);
    epoll.setLoop(true);
    epoll.eventLoop();
    UploadLocalData uploadDataListener;
    epoll.setEpollEventListener(&uploadDataListener);
    epoll.updateEvent()
    return 0;
}
