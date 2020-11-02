//
// Created by guoshichao on 19-8-2.
//

#ifndef CPPADVENTURE_BNSIMPLEFUNC_H
#define CPPADVENTURE_BNSIMPLEFUNC_H

#include <utils/RefBase.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>
#include <utils/Mutex.h>
#include "ISimpleFunc.h"

namespace adasplus {
    class BnSimpleFunc : public android::BnInterface<ISimpleFunc> {
    public:
        BnSimpleFunc();

        ~BnSimpleFunc();

        virtual android::status_t onTransact(uint32_t code,
                                             const android::Parcel &data,
                                             android::Parcel *reply,
                                             uint32_t flags = 0);
    };

    class SimpleFunc : public BnSimpleFunc {
    public:
        SimpleFunc();

        ~SimpleFunc();

    public:
        int addFunc(int firstNum, int secondNum);

        int multiplyFunc(int firstNum, int secondNum);
    };
}


#endif //CPPADVENTURE_BNSIMPLEFUNC_H
