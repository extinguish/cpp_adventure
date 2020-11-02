//
// Created by guoshichao on 19-12-30.
//

#ifndef CPPADVENTURE_ALOOPEROSTER_H
#define CPPADVENTURE_ALOOPEROSTER_H

#include "ALooper.h"
#include <map>

namespace adasplus {
    struct ALooperRoster {
        ALooperRoster();

        ALooper::handler_id registerHandler(const ALooper *looper,
                const AHandler **handler);

        void unregisterHandler(ALooper::handler_id handlerID);
        void unregisterStateHandlers();

        status_t postMessage(const AMessage **message, int64_t delayUs = 0);

        void deliverMessage(const AMessage **message);

        status_t postAndWaitResponse(const AMessage **message, AMessage **response);

        void postReply(uint32_t replyID, const AMessage **reply);

        ALooper *findLooper(ALooper::handler_id handlerID);

    private:
        struct HandlerInfo {
            ALooper *mLooper;
            AHandler *mHandler;
        };

        Mutex mLock;
        std::map<ALooper::handler_id, HandlerInfo> mHandlers;
        ALooper::handler_id mNextHandlerID;
        uint32_t mNextReplyID;
        Condition mRepliesCondition;
        std::map<uint32_t, AMessage *> mReplies;

        DISALLOW_EVIL_CONSTRUCTORS(ALooperRoster);

    };


}

#endif //CPPADVENTURE_ALOOPEROSTER_H
