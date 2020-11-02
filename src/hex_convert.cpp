//
// Created by guoshichao on 2020/4/23.
//

#include <stdio.h>

void hexToDecFormat(int hexVal, int *decFormat) {
    if (hexVal < 0x0a) {
        *decFormat = hexVal;
    }
    *decFormat = hexVal - 6;
}

int main(int argc, char **argv) {
    int warningType = 0x10;
    int warningType1 = 0x11;
    int warningType2 = 0x12;
    int warningType3 = 0x20;
    int warningType4 = 0x2A;
    int target;
    hexToDecFormat(warningType, &target);
    printf("target are %d\n", target);
    hexToDecFormat(warningType1, &target);
    printf("target are %d\n", target);
    hexToDecFormat(warningType2, &target);
    printf("target are %d\n", target);
    hexToDecFormat(warningType3, &target);
    printf("target are %d\n", target);
    hexToDecFormat(warningType4, &target);
    printf("target are %d\n", target);
}