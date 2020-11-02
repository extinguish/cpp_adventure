//
// Created by guoshichao on 2020/8/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *str = NULL;
    /* Initial memory allocation */
//    str = (char *) malloc(15);
//    strcpy(str, "tutorialspoint");
//    printf("String = %s,  Address = %u\n", str, str);

    /* Reallocating memory */
    for (int i = 0; i < 100; ++i) {
        str = (char *) realloc(str, 25 + i * 10);
        strcat(str, ".com");
        printf("String = %s,  Address = %u\n", str, str);
    }

    free(str);

    return (0);
}

