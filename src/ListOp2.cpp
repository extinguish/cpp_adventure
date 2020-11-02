//
// Created by guoshichao on 19-12-17.
//

#include <iostream>
#include <list>


typedef struct {
    int x;
    int y;
} ElemTest;

#define kPathLength 2014

typedef struct {
    unsigned char mediaType; // 文件类型
    unsigned int mediaId;
    char mediaPath[kPathLength]; // 文件名称
    char mediaName[kPathLength]; // 文件名称
    unsigned int mediaFileSize; // 当前上传文件的大小
    unsigned char mediaSerialNum; // 用于区分相同通道,相同类型的文件编号
    unsigned char channel; // 通道号
    unsigned char warningType; // 报警类型
    unsigned char warningIdentification[17]; // 报警标识号
} MediaInfo;

int main(int argc, char **argv) {
    std::list<MediaInfo *> mMediaList;
    MediaInfo *info1 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info2 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info3 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info4 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info5 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info6 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info7 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info8 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    MediaInfo *info9 = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));

    info1->mediaId = 100;
    info2->mediaId = 200;
    info3->mediaId = 300;
    info4->mediaId = 400;
    info5->mediaId = 500;
    info6->mediaId = 600;
    info7->mediaId = 700;
    info8->mediaId = 800;
    info9->mediaId = 900;

    mMediaList.push_back(info1);
    mMediaList.push_back(info2);
    mMediaList.push_back(info3);
    mMediaList.push_back(info4);
    mMediaList.push_back(info5);
    mMediaList.push_back(info6);
    mMediaList.push_back(info7);
    mMediaList.push_back(info8);
    mMediaList.push_back(info9);

    std::cout << "---------------------------------------------" << std::endl;
    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {

        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 200) {
            iterator = mMediaList.erase(iterator);
            ++iterator;
            continue;
        } else {
            // we do not remove elements from mMediaList while iterating over it
            ++iterator;
        }
    }

    std::cout << "--------------------START TO DUMP CONTENT--------------" << std::endl;
    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end(); ++iterator) {

        MediaInfo *mediaInfo = *iterator;
        // we do not remove elements from mMediaList while iterating over it
        std::cout << "elem = " << mediaInfo->mediaId << std::endl;
    }
    std::cout << "-----------------END OF DUMP CONTENT----------------" << std::endl;


    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {

        MediaInfo *mediaInfo = *iterator;
        // we do not remove elements from mMediaList while iterating over it
        ++iterator;
    }
    std::cout << __LINE__ << std::endl;


    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {
        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 100) {
            std::cout << "find 100" << std::endl;
            // we do not remove elements from mMediaList while iterating over it
            mMediaList.erase(iterator++);
            free(mediaInfo);
        } else {
            ++iterator;
        }
    }
    std::cout << "list size are " << mMediaList.size() << std::endl;


    std::cout << "now the lis size are " << mMediaList.size() << std::endl;

    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {
        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 100) {
            std::cout << "find 100" << std::endl;
            // we do not remove elements from mMediaList while iterating over it
            mMediaList.erase(iterator++);
            free(mediaInfo);
        } else {
            std::cout << "elem :" << mediaInfo->mediaId << std::endl;
            ++iterator;
            // std::cout << "not target" << std::endl;
        }
    }
    std::cout << "--->over<---" << std::endl;

    // take care of the difference of remove and erase
    // which is important
    std::cout << "media list size " << mMediaList.size() << std::endl;
    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {
        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 200) {
            // we do not remove elements from mMediaList while iterating over it
            iterator = mMediaList.erase(iterator);
            free(mediaInfo);
        }
        ++iterator;
    }

    std::cout << "--->200 over<---" << std::endl;

    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end(); ++iterator) {
        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 300) {
            // we do not remove elements from mMediaList while iterating over it
            mMediaList.remove(mediaInfo);
            free(mediaInfo);
            break;
        }
    }

    std::cout << "--->300 over<---" << std::endl;

    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {
        MediaInfo *mediaInfo = *iterator;
        if (mediaInfo->mediaId == 100) {
            // we do not remove elements from mMediaList while iterating over it
            mMediaList.remove(*iterator++);
            free(mediaInfo);
        }
        ++iterator;
    }
    std::cout << "--->remove over<---" << std::endl;

    std::cout << "media list size " << mMediaList.size() << std::endl;
    return 0;

}

