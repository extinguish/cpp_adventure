//
// Created by guoshichao on 2020/12/11.
//

#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char **argv) {
    std::string test{"00_01_23_19234335.mp4"};
    std::stringstream ss{test};
    std::string token;
    int i = 0;
    while (std::getline(ss, token, '_')) {
        if (i == 0) {
            std::cout << "media type are " << token << std::endl;
        }
        if (i == 1) {
            std::cout << "media channel are " << token << std::endl;
        }
        if (i == 2) {
            std::cout << "media event are " << token << std::endl;
        }
        if (i == 3) {
            std::cout << "media timestamp are " << token << std::endl;
        }
        ++i;
    }
    return 0;

}


