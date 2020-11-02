//
// Created by guoshichao on 19-8-2.
//

#ifndef CPPADVENTURE_ISIMPLEFUNC_H
#define CPPADVENTURE_ISIMPLEFUNC_H

#include <binder/IInterface.h>
#include <binder/IBinder.h>


namespace adasplus {
    enum {
        ADD_FUNC = android::IBinder::FIRST_CALL_TRANSACTION,
        MULTIPLY_FUNC,
    };

    class ISimpleFunc : public android::IInterface {
    public:
        virtual int addFunc(int firstNum, int secondNum) = 0;

        virtual int multiplyFunc(int firstNum, int secondNum) = 0;

        DECLARE_META_INTERFACE(SimpleFunc);
    };

}


#endif //CPPADVENTURE_ISIMPLEFUNC_H
