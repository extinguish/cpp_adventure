/// this program are mainly using to verify one problem:
/// Is it possible to call constructor and destructor explicitly ?
// 结论是可以的
// 以下是调用的方式
#include <iostream>

using namespace std;

class ExplictInvokeTest {
public:
    ExplictInvokeTest() {
        cout << "ExplictInvokeTest constructor is invoked " << endl;
    }

    ~ExplictInvokeTest() {
        cout << "ExplictInvokeTest de-constructor is invoked " << endl;
    }
};

/// 同ExplictInvokeTest的作用一样，只是这里会在ExplictInvokeTest2
/// 的成员函数当中直接显式的调用constructor和de-constructor
class ExplictInvokeTest2 {
public:
    ExplictInvokeTest2() {
        cout << "ExplictInvokeTest2 invoke the constructor" << endl;
    }

    ~ExplictInvokeTest2() {
        cout << "ExplictInvokeTest2 invoke the de-constructor" << endl;
    }

    void show() {
        ExplictInvokeTest2();
        this->ExplictInvokeTest2::~ExplictInvokeTest2();
    }
};

int main() {
    ExplictInvokeTest();
    ExplictInvokeTest test;
    test.~ExplictInvokeTest();

    ExplictInvokeTest2 test2;
    test2.show();
    return 1;
}
// When the constructor is called explicitly the compiler creates a nameless temporary
// object and it is immediately destroyed. That’s why 2nd line in the output is call
// to destructor.

/// 以下是来自于C++之父的解说(即为什么C++允许用户手动的调用constructor和de-constructor)
/// temporary objects of the class types are useful

// 然后是来自于C++标准当中的解释:
// Once a destructor is invoked for an object, the object no longer exists; the
// behavior is undefined if the destructor is invoked for an object whose lifetime
// has ended [Example: if the destructor for an automatic object is explicitly invoked,
// and the block is subsequently left in a manner that would ordinarily invoke implicit
// destruction of the object, the behavior is undefined. —end example ].
// Local objects are automatically destroyed by compiler when they go out of scope and
// this is the guarantee of C++ language. In general, special member functions shouldn’t
// be called explicitly.
