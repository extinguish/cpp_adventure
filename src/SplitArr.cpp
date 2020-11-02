//
// Created by guoshichao on 2020/5/9.
//

#include <stdio.h>

int main(int argc, char **argv) {
    int arr[996] = {0};
    const int splitPart = 100;
    size_t arrLen = 996;

    int redundant = 0;
    if (arrLen % splitPart != 0) {
        redundant = arrLen % splitPart;
    }
    int partCount = arrLen / splitPart;
    int index = 0;
    for (int i = 0; i < partCount; --partCount) {
        printf("%d --> %d \n", index, splitPart);
        ++index;
    }
    printf("%d --> %d\n", index, redundant);

}

