//
// Created by guoshichao on 20-1-14.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char path[128] = {0};
    const char *pathName = "guoshichao";
    strcpy(path, pathName);

    printf("path => %s, len=%d\n", path, strlen(path));


}

