//
// Created by guoshichao on 19-8-2.
//

#include <binder/Parcel.h>
#include "BpSimpleFunc.h"
#include <stdio.h>

adasplus::BpSimpleFunc::BpSimpleFunc(const sp<IBinder> &impl) : BpInterface(impl) {

}

adasplus::BpSimpleFunc::~BpSimpleFunc() {

}

int adasplus::BpSimpleFunc::addFunc(int firstNum, int secondNum) {
    Parcel data, reply;
    data.writeInt32(firstNum);
    data.writeInt32(secondNum);
    remote()->transact(ADD_FUNC, data, &reply);
    if (reply.readExceptionCode() != 0) {
        printf("fail to invoke the add func\n");
        return -1;
    }
    return reply.readInt32();
}

int adasplus::BpSimpleFunc::multiplyFunc(int firstNum, int secondNum) {
    Parcel data, reply;
    data.writeInt32(firstNum);
    data.writeInt32(secondNum);
    remote()->transact(MULTIPLY_FUNC, data, &reply);
    if (reply.readExceptionCode() != 0) {
        printf("fail to invoke the multiply func\n");
        return -1;
    }
    return reply.readInt32();
}
