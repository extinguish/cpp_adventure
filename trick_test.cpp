//
// Created by guoshichao on 18-10-11.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <malloc.h>

using std::cout;
using std::endl;

class SimpleContainer {
public:
    SimpleContainer(char *user_name, char *another_user_name) : user_name(user_name),
                                                                      another_user_name(another_user_name) {}

    ~SimpleContainer() {
        delete user_name;
        free(another_user_name);
    }

    char *getUserName() {
        return this->user_name;
    }

    char *getAnotherUserName() {
        return this->another_user_name;
    }

private:
    char *user_name;
    char *another_user_name;
};

void testStrConstant() {
    // 当我们直接将test_name传递给SimpleContainer的构造函数时，
    // 那么SimpleContainer的析构函数就无法调用 delete user_name
    // 否则就会报地址错误
    // 这主要是因为test_name本身是一个"字符串常量"，(而SimpleContainer
    // 构造函数初始化时，user_name是直接按位复制的test_name,即user_name和test_name指向的是
    // 同一个地方，即user_name也是字符串常量了)
    // 而"字符串常量"本身并不是直接保存在"堆栈"当中，而是保存在编译器分配的一个特殊常量区域当中
    // 而这个区域是不可直接寻址的，因此也就不存在使用delete来释放test_name了
    // 这样的话，使用delete来删除user_name就会报内存SIGV错误了
    // 但是如果我们将test_name复制到another_test_name这个变量当中，那么another_test_name
    // 就将test_name从常量区复制到了堆栈当中，然后使用another_test_name来初始化user_name
    // 的话，user_name指向的就是位于堆栈当中的内存了，这样使用delete user_name
    // 来清理user_name就没有任何问题了.
    char *test_name = "dynamic algorithm designer";
    char *another_test_name = new char[strlen(test_name)];
    memcpy(another_test_name, test_name, strlen(test_name));
    char *another_user_name = static_cast<char *>(malloc(strlen(test_name)));
    memcpy(another_user_name, test_name, strlen(test_name));
    SimpleContainer *simpleContainer = new SimpleContainer(another_test_name, another_user_name);

    cout << simpleContainer->getUserName() << endl;
    cout << "another user name are : " << simpleContainer->getAnotherUserName() << endl;
    delete simpleContainer;
}


int main(void) {
    testStrConstant();
    return 0;
}
