//
// Created by guoshichao on 2020/4/24.
//

#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void formatIPAddress(char *srcIpAddress, char *formatIPAddress) {
    const char *splitToken = "\\.";
    int ipElemArr[4] = {0};
    char val[15] = {0};
    memcpy(val, srcIpAddress, 15);
    char *attribute = strtok(val, splitToken);
    int i = 0;
    while (attribute != NULL) {
        printf("attr : %s\n", attribute);
        ipElemArr[i] = atoi(attribute);
        ++i;
        attribute = strtok(NULL, splitToken);
    }

    for (int j = 0; j < 4; ++j) {
        printf("--> %d \n", ipElemArr[j]);
    }

    sprintf(formatIPAddress, "%d.%d.%d.%d", ipElemArr[0], ipElemArr[1], ipElemArr[2], ipElemArr[3]);
    formatIPAddress[15] = '\0';
}

void splitFileName(char *fullFilePath) {
    // a sample file download url are like /safe/03_00_0_0_12/03_00_0_0_12.bin
    const char *splitToken = "\\/";
    printf("-->\n");
    char test[128] = {0};
    strcpy(test, fullFilePath);
    test[strlen(fullFilePath)] = '\0';

    char *path = strtok(test, splitToken);
    char *fileName = NULL;
    while (path != NULL) {
        fileName = path;
        path = strtok(NULL, splitToken);
        printf("path --> %s\n", path);
    }

    printf("file name are %s\n", fileName);
}

void splitFileName1(char *fullFilePath) {
    const char *splitToken = "\\.";
    char test[128] = {0};
    strcpy(test, fullFilePath);
    test[strlen(fullFilePath)] = '\0';


}

int main(int argc, char **argv) {
    char *testIpAddress = "218.028.140.212";
    char targetIpAddress[16] = {0};
    formatIPAddress(testIpAddress, targetIpAddress);
    printf("the formatted ip address are %s\n",targetIpAddress);

    char *filePath = "/safe/03_00_0_0_12/03_00_0_0_12.bin";
    splitFileName(filePath);
    char *filePath1 = "VideoMainStreamChn1_200528181200.h264";
    splitFileName1(filePath1);

}

