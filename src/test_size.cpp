//
// Created by guoshichao on 2020/7/2.
//

#include <stdio.h>
#include <strings.h>
#include <inttypes.h>
#include <string.h>

#define R 10
#define C 20

typedef struct {
    uint64_t timeStamp;//时间
    uint8_t mediaType;//媒体类型 1：音频 2:视频
    uint8_t frameType;//帧类型
    uint8_t frameRate;//帧率
    uint8_t iFrameInterval;//帧间隔
    uint64_t warningFlag;//报警标识
    uint64_t OFFSET;//偏移
    uint32_t frameSize;//帧长度
}__attribute__((packed)) StaticVideoFrameInfo;

typedef struct {
    uint64_t timeStamp;//时间
    uint8_t mediaType;//媒体类型 1：音频 2:视频
    uint8_t frameType;//帧类型
    uint8_t frameRate;//帧率
    uint8_t iFrameInterval;//帧间隔
    uint64_t warningFlag;//报警标识
    uint64_t OFFSET;//偏移
    uint32_t frameSize;//帧长度
    uint64_t gpsTimeStamp;//GPS时间戳
}__attribute__((packed)) H264MediaIndex;

void test1() {
    int (*p)[R][C];
    printf("%d", sizeof(*p));
    getchar();
}

int main() {
    size_t firstSize = sizeof(StaticVideoFrameInfo);
    size_t secondSize = sizeof(H264MediaIndex);
    H264MediaIndex first;
    first.timeStamp = 123456789;
    first.mediaType = 3;
    first.frameType = 10;
    first.frameRate = 200;
    first.iFrameInterval = 123;
    first.warningFlag = 987654321;
    first.OFFSET = 34345656;
    first.frameSize = 10203040;
    first.gpsTimeStamp = 989898;

    StaticVideoFrameInfo target;
    memcpy(&target, &first, sizeof(H264MediaIndex) - sizeof(uint64_t));
    printf("first = %zu, second = %zu\n", firstSize, secondSize);

    printf("timestamp %ld, mediaType %d, frameType %d, frameRate %d, iFrameInterval %d, warningFlag %ld, offset %ld, frameSize %d\n",
           target.timeStamp,
           target.mediaType,
           target.frameType,
           target.frameRate,
           target.iFrameInterval,
           target.warningFlag,
           target.OFFSET,
           target.frameSize);
    return 0;
}