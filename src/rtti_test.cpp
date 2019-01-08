// 关于RTTI(Runtime type information)的一些介绍
// In C++, RTTI (Run-time type information) is a mechanism that exposes information
// about an object’s data type at runtime and is available only for the classes which
// have at least one "virtual function". It allows the type of an object to be determined
// during program execution
// 例如dynamic_cast<T>就是使用RTTI实现的
#include <iostream>

using namespace std;
// 如果B当中没有任何virtual方法的话，那么编译main()函数的话
// 会报错：
// source type is not polymorphic
// 即使某些编译器编译通过，运行时也会报相同的错误
// 但是在Java当中这种情况就是合情合理的(可能是因为在Java当中所有Class都是直接继承自Object
// 对"多态"的处理理念同C++有差别)
class B {
    virtual void fun() {}
};

class D : public B {

};

int main() {
    B *b = new D;
    D *d = dynamic_cast<D *>(b);
    if (d != nullptr) {
        cout << "works" << endl;
    } else {
        cout << "cannot cast from B to D" << endl;
    }
    // 这里添加上getchar()调用，是为了防止在Windows上运行时，一瞬间闪过CMD页面
    // 在Linux上没有这个问题，因为我们是直接在terminal当中运行的(这里只是为了习惯，所以添加了   )
    getchar();
    return 1;
}

