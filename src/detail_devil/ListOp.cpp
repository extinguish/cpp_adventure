//
// Created by guoshichao on 19-6-25.
//

#include <vector>
#include <iostream>

#include <stdio.h>

template<typename ELEM>
void clearVector(std::vector<ELEM *> *list);

template<typename ELEM>
void clearVector(std::vector<ELEM *> *list) {
    for (typename std::vector<ELEM *>::iterator iter = list->begin();
         iter != list->end(); ++iter) {
        ELEM *elem = *iter;
        printf("elem %d ", *elem);
    }
    printf("\n");
}

typedef struct {
    int val;
} IntEntry;

int main(int argc, char **argv) {
    std::vector<IntEntry *> entriesList;
    IntEntry firstEntry;
    firstEntry.val = 10;
    IntEntry secondEntry;
    secondEntry.val = 20;
    entriesList.push_back(&firstEntry);
    entriesList.push_back(&secondEntry);
    clearVector(&entriesList);

#ifdef P_808_2019
    std::cout << "the new protocol" << std::endl;
#endif

    return 0;
}

