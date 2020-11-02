//
// Created by guoshichao on 2020/9/8.
//

#include <iostream>

bool isPrivate = false;

bool needDrop(unsigned char warningSrcType, unsigned char warningType) {
    if (isPrivate) {
        return false;
    }
    switch (warningSrcType) {
        case 1:
            if ((warningType >= 0x09 && warningType <= 0x0F) || (warningType >= 0x12 && warningType <= 0xFF)) {
                return true;
            }
            break;
        case 2:
            if ((warningType >= 0x08 && warningType <= 0x0F) || (warningType >= 0x12 && warningType <= 0xFF)) {
                return true;
            }
            break;
    }
    return false;
}


int main(int argc, char **argv) {
    if (needDrop(1, 0x13)) {
        std::cout << "0x13" << std::endl;
    }

    if (needDrop(1, 0x1)) {
        std::cout << "0x1 warning" << std::endl;
    } else {
        std::cout << "test" << std::endl;
    }
}
