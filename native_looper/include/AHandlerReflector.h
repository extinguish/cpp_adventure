//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_AHANDLERREFLECTOR_H
#define CPPADVENTURE_AHANDLERREFLECTOR_H

#include "AHandler.h"

namespace adasplus {
    template<typename T>
    struct AHandlerReflector : public AHandler {
        AHandlerReflector(T *target) : mTarget(target){

        }

    protected:
        virtual void onMessageReceived(const AMessage *msg) {

        }
    private:
        T *mTarget;
        AHandlerReflector(const AHandlerReflector<T> &);
        AHandlerReflector<T> &operator=(const AHandlerReflector<T> &);
    };

}

#endif //CPPADVENTURE_AHANDLERREFLECTOR_H
