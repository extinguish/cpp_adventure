//
// Created by guoshichao on 19-4-8.
//

#include <cstdio>
#include <cstring>

#include <vector>

int main(int argc, char **argv) {

    const char *name = "t";

    char nameArr[5];
    memcpy(nameArr, name, 5);
    nameArr[5] = '\0';
    printf("name are %s\n", nameArr);

    std::vector<int> intVec;
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);

    for (std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it) {
        int val = *it;
        printf("%d ", val);
    }
    printf("\n");

}


