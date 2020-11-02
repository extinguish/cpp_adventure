//
// Created by guoshichao on 19-5-6.
//

#include "TerminalFileObserver.h"
#include <string>

namespace adasplus {
    class FileMonitor : public ITakePhotoFileMonitorCallback {
    public:
        void onPhotoFile(const char *photoName);
    };

    void FileMonitor::onPhotoFile(const char *photoName) {
        printf("on created photo file of %s\n", photoName);
    }
}

int main(int argc, char **argv) {
    adasplus::FileMonitor fileMonitor;
    std::string monitorPath{"/home/keytch"};
    adasplus::TakePhotoFileObserver takePhotoFileObserver{monitorPath, adasplus::ALL_EVENTS};
    takePhotoFileObserver.setTakePhotoFileMonitorCallback(&fileMonitor);
}
