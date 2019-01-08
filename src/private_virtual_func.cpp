// 这里主要是分析"Can virtual functions be private in C++"
// 先说一下结论:"In C++, virtual functions
// can be private and can be overridden by the derived class."
// 以下就是这样的实现:
#include <iostream>
using namespace std;

class Derived;

class Base {
private:
    virtual void fun() {
        cout << "Inside Base class" << endl;
    }

    // 这是整个技巧的关键点
    friend int main();
};

class Derived : public Base {
public:
    void fun() {
        cout << "Inside Derived class" << endl;
    }
};

int main() {
    Base *ptr = new Derived;
    ptr->fun();
    return 1;
}

// 以下是整个技巧实现的内部说明:
// 1) ptr is a pointer of "Base" type and points to a "Derived" class object.
// When "ptr->fun()" is called, fun() of Derived is executed. // 可以参考src/private_virtual_fun_2.cpp当中的实现分析
// 2) int main() is a friend of Base.  If we remove this friendship, the program
// won’t compile. We get compiler error.
// Note that this behavior is totally different in Java. In Java, private methods
// are final by default and cannot be overridden.