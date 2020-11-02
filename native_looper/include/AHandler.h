//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_AHANDLER_H
#define CPPADVENTURE_AHANDLER_H

namespace adasplus {
    struct AMessage;

    struct AHandler {

        AHandler() : mID(0) {}

    protected:
        virtual void onMessageReceived(const AMessage *msg) = 0;

    private:
        friend struct ALooperRoster;

        ALooper::handler_id mID;

        void setID(ALooper::handler_id id) {
            mID = id;
        };

        DISALLOW_EVIL_CONSTRUCTORS(AHandler);
    };

}

#endif //CPPADVENTURE_AHANDLER_H
