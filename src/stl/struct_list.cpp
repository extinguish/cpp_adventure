//
// Created by guoshichao on 19-8-6.
//

#include <stdio.h>
#include <list>
#include <vector>
#include <cstdlib>
#include <cstring>

typedef struct {
    unsigned char mediaType; // 文件类型
    unsigned int mediaId;
    char mediaPath[64]; // 文件名称
    char mediaName[64]; // 文件名称
    unsigned int mediaFileSize; // 当前上传文件的大小
    unsigned char mediaSerialNum; // 用于区分相同通道,相同类型的文件编号
    unsigned char channel; // 通道号
    unsigned char warningType; // 报警类型
    unsigned char warningIdentification[17]; // 报警标识号
} MediaInfo;

typedef struct dmsData {
    unsigned int warningId; // 0 报警 ID
    unsigned char flag; // 4 标志状态
    unsigned char warningType; // 5 报警/事件类型
    unsigned char warningLevel; // 6 报警级别
    unsigned char fatigueLevel; // 7 疲劳程度
    unsigned char back1[4]; // 8 预留
    unsigned char speed; // 12 车速
    unsigned short altitude; // 13 高程
    unsigned int latitude; // 15 纬度
    unsigned int longtitude; // 19 经度
    unsigned char time[6]; // 23 日期时间
    unsigned short carState; // 29 车辆状态
    unsigned char warningIdentification[16]; // 31 报警标识号
    unsigned char mediaCount;
    // MediaInfo *mediaInfo;
    // std::vector<MediaInfo *> mediaInfo;
    std::list<MediaInfo *> mediaInfoList{};
} DmsData;


int main(int argc, char **argv) {
    printf("%s %d\n", __func__, __LINE__);
    DmsData *dmsData = static_cast<DmsData *>(malloc(sizeof(DmsData)));
    printf("%s %d\n", __func__, __LINE__);
    memset(dmsData, 0, sizeof(DmsData));
    printf("%s %d\n", __func__, __LINE__);
    MediaInfo *mediaInfo = static_cast<MediaInfo *>(malloc(sizeof(MediaInfo)));
    printf("%s %d\n", __func__, __LINE__);
    memset(mediaInfo, 0, sizeof(MediaInfo));
    printf("%s %d\n", __func__, __LINE__);
    mediaInfo->mediaId = 100;
    printf("%s %d\n", __func__, __LINE__);
    // dmsData->mediaInfoList = ;
    dmsData->mediaInfoList.push_back(mediaInfo);
    printf("%s %d\n", __func__, __LINE__);


}

