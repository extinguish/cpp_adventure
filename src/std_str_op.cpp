//
// Created by guoshichao on 2020/12/23.
//

#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::string ftpServerIp{"192.168.100.100"};
    std::string ftpPort{"100"};
    std::string ftpUsrName{"scguo"};
    std::string ftpUsrPsw{"123455"};
    std::string otaFileName{"test.zip"};
    std::string otaFilePath{"/path/home/scguo"};

    std::string fullFtpAddress =
            "ftp://" + ftpUsrName + ":" + ftpUsrPsw + "@" + ftpServerIp + ":" + ftpPort
            + otaFilePath + otaFileName;

    std::cout << fullFtpAddress << std::endl;

    return 0;
}

