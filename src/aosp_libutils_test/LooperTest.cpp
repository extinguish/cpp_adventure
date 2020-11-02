//
// Created by guoshichao on 19-1-25.
//
#include "../aosp_libutils/include/Looper.h"
#include "../aosp_libutils/include/Timers.h"
#include "../aosp_libutils/include/StopWatch.h"

#include <unistd.h>
#include <time.h>
#include <iostream>

using android::sp;
using android::Looper;
using android::LooperCallback;
using android::MessageHandler;
using android::Message;


using std::cout;
using std::cin;
using std::endl;

const int onDataReadyMsgId = 100;
sp<Looper> looperRef;
Looper *looper;

class SimpleMsgHandler : public MessageHandler {
    void handleMessage(const Message &message);
};

void SimpleMsgHandler::handleMessage(const Message &message) {
    cout << "handle message of " << message.what << endl;
    if (message.what == onDataReadyMsgId) {
        looper->sendMessageDelayed(1 * 1000 * 1000, this, message);
    }
}

int main(int args, char **argv) {
    looperRef = new Looper(false);
    looper = looperRef.get();

    Looper::prepare(0);

    sp<SimpleMsgHandler> msgHandlerRef = new SimpleMsgHandler();

    Message msg{onDataReadyMsgId};
    cout << endl;
    cout << "===================================" << endl;
    cout << "start send out message " << endl;
    looper->sendMessage(msgHandlerRef, msg);

    // the following line are just using to ensure the current process do not dead
    sleep(10000000);
}
