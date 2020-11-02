//
// Created by guoshichao on 19-3-15.
//

#ifndef SUBIAOTERMINAL_TERMINALFILEOBSERVER_H
#define SUBIAOTERMINAL_TERMINALFILEOBSERVER_H

#include "common/FileObserver.h"
#include <string>
#include <cstring>

#define FILE_TYPE_IMAGE 1
#define FILE_TYPE_VIDEO 2

#define DMS_WARNING_FILE_NAME_ATTRIBUTES_NUM 10
#define ADAS_WARNING_FILE_NAME_ATTRIBUTES_NUM 12

#define PHOTO_FILE_ATTRIBUTES_NUM 6

#define VIDEO_FILE_SUFFIX ".mp4"
#define IMAGE_FILE_SUFFIX ".jpg"

#define PHOTO_FILE_PATH "/home/keytech/photo"

#define LOGE(...) printf(__VA_ARGS__)

// TODO: we may do not need this file observer any more
namespace adasplus {

    // the path of which the warning file will be store
    static std::string ADAS_WARNING_FILE_PATH{"/home/keytech/warning/adas"};
    static std::string DMS_WARNING_FILE_PATH{"/home/keytech/warning/dms"};
    // the path of which the taken photo will be store
    static std::string ADAS_TAKE_PHOTO_FILE_PATH{PHOTO_FILE_PATH};

    // the callback of which will be notified when new adas warning file or dms warning file is generated
    class IWarningFileMonitorCallback {
    public:
        virtual void onWarningFile(unsigned char channel, int fileType, const char *filePath) = 0;

    public:
        ~IWarningFileMonitorCallback() = default;
    };

    // the callback of which will be notified when newly take photo is generated
    class ITakePhotoFileMonitorCallback {
    public:
        virtual void onPhotoFile(const char *photoName) = 0;

    public:
        ~ITakePhotoFileMonitorCallback() = default;
    };

    class AdasWarningFileObserver : public FileObserver {
    public:

        AdasWarningFileObserver(std::string &path, int mask = ALL_EVENTS);

        ~AdasWarningFileObserver();

        // implemented from FileObserver
        void onEvent(int wfd, int mask, const char *path);

    public:
        void setAdasWarningFileMonitorCallback(IWarningFileMonitorCallback *callback);

    private:
        IWarningFileMonitorCallback *mAdasFileCallback;
    };

    class DmsWarningFileObserver : public FileObserver {
    public:
        DmsWarningFileObserver(std::string &path, int mask = ALL_EVENTS);

        ~DmsWarningFileObserver();

        // implemented from FileObserver
        void onEvent(int wfd, int mask, const char *path);

    public:
        void setDmsWarningFileMonitorCallback(IWarningFileMonitorCallback *callback);

    private:
        IWarningFileMonitorCallback *mDmsFileCallback;
    };

    class TakePhotoFileObserver : public FileObserver {
    public:
        TakePhotoFileObserver(std::string &path, int mask = ALL_EVENTS);

        ~TakePhotoFileObserver();

        // implemented from FileObserver
        void onEvent(int wfd, int mask, const char *path);

    public:
        void setTakePhotoFileMonitorCallback(ITakePhotoFileMonitorCallback *callback);

    private:
        ITakePhotoFileMonitorCallback *mTakePhotoFileCallback;
    };

}

#endif //SUBIAOTERMINAL_TERMINALFILEOBSERVER_H
