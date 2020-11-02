//
// Created by guoshichao on 19-7-25.
//
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>
#include <algorithm>


#ifdef HAVE_ST_BIRTHTIME
#define birthtime(x) x.st_birthtime
#else
#define birthtime(x) x.st_ctime
#endif

#define PERSIST_BASE_DIR "/home/guoshichao/scguo_crash/crash_07_24"

typedef struct {
    struct dirent *dirEntry;
    long creationTime;
} DirInfo;

long getDirCreationTime(char *dir) {
    char targetDir[256] = {0};
    sprintf(targetDir, "%s/%s", PERSIST_BASE_DIR, dir);
    struct stat st;
    if (stat(targetDir, &st) != 0) {
        printf("fail to get the creation time of %s, %s\n", targetDir, strerror(errno));
        return 0;
    }
    return birthtime(st);
}

bool compareDirectory(DirInfo *first, DirInfo *secondDir) {
    return first->creationTime > secondDir->creationTime;
}

void truncateDir() {
    DIR *directory = NULL;
    struct dirent *dirEntry;
    directory = opendir(PERSIST_BASE_DIR);
    if (directory == NULL) {
        printf("FATAL ERROR!!! fail to open the %s, caused by %s\n", PERSIST_BASE_DIR, strerror(errno));
        return;
    }
    std::vector<DirInfo *> dirInfoList;
    while ((dirEntry = readdir(directory)) != NULL) {
        printf("directory %s, dt type are %d\n", dirEntry->d_name, dirEntry->d_type);
        if (strcmp(dirEntry->d_name, ".") == 0) {
            printf("--------------> is CURRENT directory\n");
            continue;
        }
        if (strcmp(dirEntry->d_name, "..") == 0) {
            printf("------------> is parent directory\n");
            continue;
        }
        if (dirEntry->d_type == DT_DIR) {
            DirInfo *dirInfo = static_cast<DirInfo *>(malloc(sizeof(DirInfo)));
            dirInfo->creationTime = getDirCreationTime(dirEntry->d_name);
            dirInfo->dirEntry = dirEntry;
            dirInfoList.push_back(dirInfo);
        }
    }
    closedir(directory);

    if (dirInfoList.size() >= (5 - 1)) {
        // sort the vector, and remove the oldest directory
        std::sort(dirInfoList.begin(), dirInfoList.end(), compareDirectory);
        for (int i = 0; i < dirInfoList.size(); ++i) {
            printf("time of %s --> %ld\n", dirInfoList[i]->dirEntry->d_name, dirInfoList[i]->creationTime);
        }

        // and now remove the oldest element
        DirInfo *oldestDir = dirInfoList.back();
        printf("the directory to remove are --> %s\n", oldestDir->dirEntry->d_name);

        dirInfoList.pop_back();
    }
}


int main(int argc, char **argv) {
    truncateDir();
}