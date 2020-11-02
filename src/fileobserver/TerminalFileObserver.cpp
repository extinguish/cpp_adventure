//
// Created by guoshichao on 19-3-15.
//

#include "TerminalFileObserver.h"

adasplus::AdasWarningFileObserver::AdasWarningFileObserver(std::string &path, int mask) : FileObserver(path, mask) {
    init();
    startWatching();
}

adasplus::AdasWarningFileObserver::~AdasWarningFileObserver() {
    stopWatching();
}

void adasplus::AdasWarningFileObserver::onEvent(int wfd, int mask, const char *path) {
    if (mAdasFileCallback != nullptr) {
        // if is image file, we need to encode this file as JPG of PNG
        // if this is raw yuv video file, we need to encode this file as mp4 or h264 format
        const char *fileSuffix = strrchr(path, '.');
        if (strcmp(fileSuffix, IMAGE_FILE_SUFFIX) == 0) {
            LOGE("generate image warning file\n");
            mAdasFileCallback->onWarningFile(64, FILE_TYPE_IMAGE, path);
        } else if (strcmp(fileSuffix, VIDEO_FILE_SUFFIX) == 0) {
            LOGE("generate video warning file\n");
            mAdasFileCallback->onWarningFile(65, FILE_TYPE_VIDEO, path);
        } else {
            LOGE("the generated file \"%s\"are unknown\n", path);
        }
    }
}

void adasplus::AdasWarningFileObserver::setAdasWarningFileMonitorCallback(
        adasplus::IWarningFileMonitorCallback *callback) {
    this->mAdasFileCallback = callback;
}

adasplus::DmsWarningFileObserver::DmsWarningFileObserver(std::string &path, int mask) : FileObserver(path, mask) {
    init();
    startWatching();
}

adasplus::DmsWarningFileObserver::~DmsWarningFileObserver() {
    stopWatching();
}

void adasplus::DmsWarningFileObserver::onEvent(int wfd, int mask, const char *path) {
    if (mDmsFileCallback != nullptr) {

        mDmsFileCallback->onWarningFile(0x65, FILE_TYPE_IMAGE, path);
    }
}

void
adasplus::DmsWarningFileObserver::setDmsWarningFileMonitorCallback(adasplus::IWarningFileMonitorCallback *callback) {
    this->mDmsFileCallback = callback;
}

adasplus::TakePhotoFileObserver::TakePhotoFileObserver(std::string &path, int mask) : FileObserver(path, mask) {
    init();
    startWatching();
}

adasplus::TakePhotoFileObserver::~TakePhotoFileObserver() {
    stopWatching();
}

void adasplus::TakePhotoFileObserver::onEvent(int wfd, int mask, const char *path) {
    if (mTakePhotoFileCallback != nullptr) {
        mTakePhotoFileCallback->onPhotoFile(path);
    }
}

void adasplus::TakePhotoFileObserver::setTakePhotoFileMonitorCallback(
        adasplus::ITakePhotoFileMonitorCallback *callback) {
    this->mTakePhotoFileCallback = callback;
}


