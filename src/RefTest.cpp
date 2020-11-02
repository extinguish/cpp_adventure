//
// Created by guoshichao on 20-1-6.
//

#include <iostream>

class TestObj {
public:
    TestObj();

    ~TestObj();

    int getCount();

private:
    int count;
};

TestObj::TestObj() {
    count = 0;
}

TestObj::~TestObj() {
    count = -1;
}

int TestObj::getCount() {
    return count;
}

int main(int argc, char **argv) {
    TestObj *firstObj = new TestObj();
    std::cout << "1 --> count value " << firstObj->getCount() << std::endl;
    delete firstObj;
    firstObj = NULL;
    firstObj = new TestObj();
    std::cout << "2 --> count value " << firstObj->getCount() << std::endl;

    TestObj *secondObj = firstObj;
    secondObj = NULL;
    std::cout << "3 --> count value " << firstObj->getCount() << std::endl;
}

