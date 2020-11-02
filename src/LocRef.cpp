//
// Created by guoshichao on 2020/5/21.
//

#include <cstdio>
#include <list>
#include <cstdlib>
#include <cstring>

typedef unsigned int BYTE;

typedef struct {
    int channelNum;

} MediaStreamClient;

std::list<MediaStreamClient *> mMediaStreamClientList;

MediaStreamClient *getTargetStreamClient(const BYTE channelNum) {
    MediaStreamClient *targetClient = nullptr;
    for (std::list<MediaStreamClient *>::iterator clientIter = mMediaStreamClientList.begin();
         clientIter != mMediaStreamClientList.end();
         ++clientIter) {
        MediaStreamClient *client = *clientIter;
        if (client->channelNum == channelNum) {
            printf("get the target channel of %d\n", channelNum);
            targetClient = client;
            break;
        }
    }
    if (targetClient == nullptr) {
        printf("create new MediaStreamClient of channel --> %d\n", channelNum);
        MediaStreamClient *client = static_cast<MediaStreamClient *>(malloc(sizeof(MediaStreamClient)));
        client->channelNum = channelNum;
        mMediaStreamClientList.push_back(client);
        targetClient = client;
    }
    return targetClient;
}


int main(int argc, char **argv) {
    MediaStreamClient *client1 = static_cast<MediaStreamClient *>(malloc(sizeof(MediaStreamClient)));
    client1->channelNum = 100;
    MediaStreamClient *client2 = static_cast<MediaStreamClient *>(malloc(sizeof(MediaStreamClient)));
    client2->channelNum = 200;
    MediaStreamClient *client3 = static_cast<MediaStreamClient *>(malloc(sizeof(MediaStreamClient)));
    client3->channelNum = 300;

    mMediaStreamClientList.push_back(client1);
    mMediaStreamClientList.push_back(client2);
    mMediaStreamClientList.push_back(client3);

    MediaStreamClient *client = getTargetStreamClient(200);
    printf("the client we get are --> %d\n", client->channelNum);
}

