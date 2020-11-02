//
// Created by guoshichao on 19-8-2.
//

#include "BnSimpleFunc.h"

using namespace android;

adasplus::BnSimpleFunc::BnSimpleFunc() {

}

adasplus::BnSimpleFunc::~BnSimpleFunc() {

}

android::status_t
adasplus::BnSimpleFunc::onTransact(uint32_t code, const android::Parcel &data, android::Parcel *reply, uint32_t flags) {
    CHECK_INTERFACE(ISimpleFunc, data, reply)
    status_t ret = android::NO_ERROR;
    switch (code) {
        case ADD_FUNC: {
            int firstNum = data.readInt32();
            int secondNum = data.readInt32();
            int result = addFunc(firstNum, secondNum);
            reply->writeNoException();
            reply->writeInt32(result);
        }
            break;
        case MULTIPLY_FUNC: {
            int firstNum = data.readInt32();
            int secondNum = data.readInt32();
            int result = multiplyFunc(firstNum, secondNum);
            reply->writeNoException();
            reply->writeInt32(result);
        }
            break;
        default: {
            printf("invoke unsupported func\n");
        }
            break;
    }

    return ret;
}

adasplus::SimpleFunc::SimpleFunc() {

}

adasplus::SimpleFunc::~SimpleFunc() {

}

int adasplus::SimpleFunc::addFunc(int firstNum, int secondNum) {
    return firstNum + secondNum;
}

int adasplus::SimpleFunc::multiplyFunc(int firstNum, int secondNum) {
    return firstNum * secondNum;
}
