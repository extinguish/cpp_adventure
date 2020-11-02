//
// Created by guoshichao on 19-2-22.
//
#include <iostream>

using namespace std;

class StaticFieldTest {
public:
    static int serialNum;
};

int StaticFieldTest::serialNum = 0;

int main(int argc, char **argv) {
    int value = StaticFieldTest::serialNum;
    cout << "the value are " << value << endl;
}

