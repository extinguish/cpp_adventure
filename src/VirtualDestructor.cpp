//
// Created by guoshichao on 2020/6/15.
//
#include <stdio.h>
#include <cstring>

class VirtualBase {
public:
    virtual ~VirtualBase() {};
};


class FirstChild : public VirtualBase {

public:
    FirstChild();

    ~FirstChild();

};

FirstChild::FirstChild() {

}

FirstChild::~FirstChild() {
    printf("destroy the FirstChild\n");
}

class SecondChild {
public:
    SecondChild();

    ~SecondChild();
};

SecondChild::SecondChild() {

}

SecondChild::~SecondChild() {
    printf("destroy the SecondChild\n");
}


int main(int argc, char **argv) {

    VirtualBase *virtualBase = new FirstChild();
    delete virtualBase;
    printf("after delete the child\n");
}

