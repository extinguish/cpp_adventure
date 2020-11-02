//
// Created by guoshichao on 19-8-2.
//

#ifndef CPPADVENTURE_DEATHNOTIFIER_H
#define CPPADVENTURE_DEATHNOTIFIER_H

#include <binder/IBinder.h>
#include <binder/ISystemServer.h>

using namespace android;

namespace adasplus {
    class IServerDeadListener {
    public:
        virtual void onServerDead() = 0;
    };

    class DeathNotifier : public IBinder::DeathRecipient {
    public:
        DeathNotifier() : mListener(NULL) {

        }

        ~DeathNotifier() {}

        void setServer(sp<ISystemServer> &server) {
            mServer = server;
        }

        virtual void binderDied(const wp<IBinder> &server/*who*/) {

            sp<IBinder> systemserver = server.promote();
            status_t ret = systemserver->unlinkToDeath(this);
            if (mListener != NULL) {
                mListener->onServerDead();
            }
        }

        void setServerDeadListener(IServerDeadListener *listener) { mListener = listener; };

    private:
        sp<ISystemServer> mServer;
        IServerDeadListener *mListener;
    };
}


#endif //CPPADVENTURE_DEATHNOTIFIER_H
