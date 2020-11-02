//
// Created by guoshichao on 2020/9/18.
//

#include <stdio.h>

const char *flatUCharArr(const unsigned char *uArr, const size_t arrLen) {
    char flatArrStr[arrLen * 2 + 1] = {0};
    sprintf(flatArrStr, "%.2x", uArr[0]);
    for (int i = 1; i < arrLen; ++i) {
        sprintf(flatArrStr, "%s%.2x", flatArrStr, uArr[i]);
    }
    flatArrStr[arrLen * 2] = '\0';
    printf("%s\n", flatArrStr);
    return flatArrStr;
}

int main(int argc, char **argv) {
    unsigned char test[6] = {0x01, 0x02, 0x03, 0x11, 0x12, 0x13};
    printf("arr length are %zu\n", sizeof(test));

    printf("the content of test are %s\n", flatUCharArr(test, sizeof(test)));
}

