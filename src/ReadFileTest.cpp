//
// Created by guoshichao on 2020/6/3.
//

#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include <errno.h>

typedef unsigned char BYTE;
typedef unsigned int DWORD;

typedef struct {
    uint64_t timeStamp;//时间
    BYTE mediaType;//媒体类型
    BYTE frameType;//帧类型
    BYTE frameRate;//帧率
    BYTE iFrameInterval;//帧间隔
    uint64_t warningFlag;//报警标识
    uint64_t OFFSET;//偏移
    DWORD frameSize;//帧长度
}__attribute__((packed)) JT1078VideoInfo;

int main() {
    FILE *indexFp;
    char indexFilePath[1024] = {0};
    sprintf(indexFilePath,
            "/media/guoshichao/04167E5E167E50A2/a_scguo_cache/06_02/VideoMainStreamChn1_200603143501.h264.idx");
    indexFp = fopen(indexFilePath, "rb");
    if (indexFp == nullptr) {
        printf("fail to open index file of %s, caused by %s\n", indexFilePath, strerror(errno));
        return -1;
    }

    size_t frameCount = 0;

    fseek(indexFp, -4, SEEK_END);
    int readResult = fread(&frameCount, 4, 1, indexFp);
    if (readResult <= 0) {
        printf("FATAL ERROR!!! fail to read out the frame count from index file\n");
        return -1;
    }
    printf("the frame count are %zu\n", frameCount);
    fseek(indexFp, 0, SEEK_SET);
    for (size_t i = 0; i < frameCount; ++i) {
        if (feof(indexFp)) {
            printf("reach the end of the index file");
            break;
        }
        JT1078VideoInfo frameInfo;
//        = static_cast<StaticVideoFrameInfo *>(malloc(sizeof(StaticVideoFrameInfo)));
        memset(&frameInfo, 0, sizeof(JT1078VideoInfo));
        fread(&frameInfo, sizeof(JT1078VideoInfo), 1, indexFp);
//        mVideoFrameInfoList.push_back(frameInfo);
        printf("frame info --> frameSize:%d, OFFSET:%ld, timestamp:%ld, type:%d\n",
               frameInfo.frameSize, frameInfo.OFFSET, frameInfo.timeStamp, frameInfo.frameType);
    }
}

