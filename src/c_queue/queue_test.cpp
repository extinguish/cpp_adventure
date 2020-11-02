//
// Created by guoshichao on 19-7-5.
//

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <strings.h>
#include <cstring>

typedef struct {
    int number;
    // char value[10];
} CameraNode;

int main(int argc, char **argv) {
    CameraNode *firstNode = static_cast<CameraNode *>(malloc(sizeof(CameraNode)));
    firstNode->number = 100;
    CameraNode *secondNode = static_cast<CameraNode *>(malloc(sizeof(CameraNode)));
    secondNode->number = 200;
    CameraNode *thirdNode = static_cast<CameraNode *>(malloc(sizeof(CameraNode)));
    thirdNode->number = 300;


//    QCameraQueue firstQueue;
//    firstQueue.init();
//
//    firstQueue.enqueue(firstNode);
//    firstQueue.enqueue(secondNode);
//    firstQueue.enqueue(thirdNode);
//    CameraNode fourthNode;
//    fourthNode.number = 400;
//    firstQueue.enqueue(&fourthNode);

    // CameraNode *node = static_cast<CameraNode *>(firstQueue.getFront());
    // printf("the node value are %d --> %s\n", node->number, node->value);
//    CameraNode *node = static_cast<CameraNode *>(firstQueue.dequeue());
//    printf("the node value are %d\n", node->number);
//    CameraNode *node2 = static_cast<CameraNode *>(firstQueue.getFront());
//    printf("the node value are %d\n", node2->number);
//
//    std::queue<CameraNode*> nodeQueue;
//    nodeQueue.push(firstNode);
//    nodeQueue.push(secondNode);
//    nodeQueue.push(thirdNode);
//    CameraNode *firstVal = nodeQueue.front();
//    int size = nodeQueue.size();
//    printf("size are %d, first value are %d \n", size, firstVal->number);
//    nodeQueue.pop();
//    CameraNode *secondVal = nodeQueue.front();
//    int currentSize = nodeQueue.size();
//    printf("second node value are %d, current size are %d\n", secondVal->number, currentSize);

    const char *fileName = "02_64_6504_1_98c31c78bdd343e18e5a8539b0b34c1c";
    if (strstr(fileName, "_64_")) {
        printf("is the adas channel\n");
    } else {
        printf("UNKNOWN CHANNEL\n");
    }


    std::queue<CameraNode*> testQueue;
    testQueue.push(firstNode);
    testQueue.push(secondNode);
    testQueue.push(thirdNode);


//    CameraNode *node1 = testQueue.front();
//    testQueue.pop();
//    free(node1);
    printf("current queue size are %d\n", testQueue.size());

    while (!testQueue.empty()) {
        CameraNode *elem = testQueue.front();
        printf("free %d\n", elem->number);
        testQueue.pop();
        free(elem);
    }



}
