//
// Created by guoshichao on 19-7-22.
//

#include <stdio.h>

#include <map>
#include <list>
#include <vector>
#include <iostream>

using namespace std;
typedef std::list<int> TESTLIST;

int main(int argc, char **argv) {
    TESTLIST t;
    for (int i = 0; i < 100; i++) {
        t.push_back(i);
    }

    for (int x = 0; x < 10; x++) {
        int index = 0;
        for (TESTLIST::iterator it = t.begin(); it != t.end();) {
            int elem = *it;
            printf("current element are --> %d : ", elem);
            // printf("remove element at %d\n", ++index);
            t.erase(it++);
            printf("element count are %d\n", t.size());
        }
        printf("---------------------------%d\n", x);
    }

    std::vector<int> intVec = {1, 100, 29, 30, 49, 300, 2, 400};

    unsigned int val = 0xFF02;
    unsigned int delta = 0xFF00;
    unsigned int result = val - delta;
    std::cout << result << std::endl;

    unsigned int val2 = delta + 0x19;
    unsigned int val3 = val2 - delta;
    std::cout << val3 << std::endl;

    return 0;
}

