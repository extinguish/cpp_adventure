//
// Created by guoshichao on 2020/7/6.
//
#include <stdio.h>
#include <iostream>
#include <list>

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

    std::cout << "before op --> media list size are " << mMediaList.size() << std::endl;
    for (std::list<MediaInfo *>::iterator iterator = mMediaList.begin();
         iterator != mMediaList.end();) {

        MediaInfo *mediaInfo = *iterator;
        mMediaList.erase(iterator++);
    }

    std::cout << "current media list size are " << mMediaList.size() << std::endl;

}
