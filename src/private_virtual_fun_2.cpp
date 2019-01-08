// C++当中的private virtual method的访问分析
#include <iostream>

using namespace std;

class Base {
public:
    virtual int fun(int i) {
        cout << "inside base class and i are : " << i << endl;
        return i;
    }
};

// 在main()函数当中，如果我们直接调用:
// Derived derived;
// derived.fun(1);
// 的话，会编译错误.
// 但是如果修改成:
// Base *basePtr = new Derived;
// basePtr->fun(10);
// 就可以了
class Derived : public Base {
private:
    int fun(int x) {
        cout << "inside the derived class the x are : " << x << endl;
    }
};

int main() {
    Base *basePtr = new Derived;
    basePtr->fun(10);

    return 1;
}

// 以下是具体的解释:
// In the above program, private function “Derived::fun(int )” is being called through
// a base class pointer, the program works fine because fun() is public in base class.
// Access specifiers are checked at "compile time" and fun() is public in base class.
// At "run time", only the function corresponding to the pointed object is called and
// access specifier is not checked. So a private function of derived class is being called
// through a pointer of base class.
// 由此再看一下private_virtual_func.cpp当中的实例:
// 我们在Base当中将main()声明为Base的friend,
// 然后我们在main当中就可以访问Base当中的private virtual func()方法了
// 同时又由于指针的动态特性，即ptr的类型是Base,但是在运行时又是指向Derived
// 因此最终又是调用了Derived当中的func()方法
// 由此也可以知道，在C++当中“多态”特性本身是在运行时发挥特性的，因此效率也相对于弱了一些.