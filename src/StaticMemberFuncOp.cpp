//
// Created by guoshichao on 2020/4/7.
//

#include <iostream>

typedef void (*funcPointer)(int, std::string &);

class TestCls {
private:
    static TestCls *instance;
    funcPointer fp;
public:
    TestCls() {
        instance = this;
    }

    void setupFp() {
        fp = staticWrapper;
    }

    void invokeFp() {
        std::string val{"keytech"};
        fp(100, val);
    }

    ~TestCls() {}

public:
    static void staticWrapper(int val, std::string &content) {
        instance->trueFunc(val, content);
    }

private:
    void trueFunc(int val, std::string &content) {
        std::cout << val << content << std::endl;
    }


};

int main(int argc, char **argv) {
    TestCls testCls;
    testCls.setupFp();
    testCls.invokeFp();
}

