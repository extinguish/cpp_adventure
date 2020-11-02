//
// Created by guoshichao on 2020/8/11.
//

#include <cstdio>


int main(int argc, char **argv) {
    char **testArr[5][6];
    int len = sizeof(testArr);
    int len1 = sizeof(*testArr);
    int len2 = sizeof(**testArr);

    int arr[5][6];
    int len3 = sizeof(arr);
    char arr1[5][6];
    int len4 = sizeof(arr1);

    printf("len = %d, len1 = %d, len2 = %d, len3 = %d, len4 = %d \n", len, len1, len2, len3, len4);


}

