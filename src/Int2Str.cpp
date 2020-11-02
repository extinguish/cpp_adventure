//
// Created by guoshichao on 19-5-5.
//
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int x = 100;
    const char *val = reinterpret_cast<const char *>(x);
    printf("the value of x are %s\n", val);

}

