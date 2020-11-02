//
// Created by guoshichao on 19-8-2.
//

#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "BpSimpleFunc.h"
#include "../server/BnSimpleFunc.h"
#include <pthread.h>

#include <stdio.h>

using namespace android;

void *startFuncService(void *args) {
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();

    if (sm == nullptr) {
        printf("fail to get the system service manager\n");
        return nullptr;
    }
    adasplus::SimpleFunc func;
    sm->addService(String16("simple_func_service"), &func);


    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return nullptr;
}

int main(int argc, char **argv) {
    pthread_t serverThreadId;
    pthread_create(&serverThreadId, nullptr, startFuncService, nullptr);





}



