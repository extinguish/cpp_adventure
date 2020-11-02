//
// Created by guoshichao on 19-8-2.
//

#ifndef CPPADVENTURE_BPSIMPLEFUNC_H
#define CPPADVENTURE_BPSIMPLEFUNC_H

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include "../server/ISimpleFunc.h"


using namespace android;

namespace adasplus {
    class BpSimpleFunc : public android::BpInterface<ISimpleFunc> {
    public:
        BpSimpleFunc(const sp<IBinder> &impl);

        ~BpSimpleFunc();

    public:
        int addFunc(int firstNum, int secondNum);

        int multiplyFunc(int firstNum, int secondNum);
    };
    IMPLEMENT_META_INTERFACE(SimpleFunc, "SimpleFuncService");

}


#endif //CPPADVENTURE_BPSIMPLEFUNC_H
