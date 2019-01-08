/// this program mainly consider the following questions:
/// when are static objects destroyed ?
/// static local variable retain their values between function call
/// and initialized only once. static function can be directly called
/// using the scope resolution operator preceded by class name(C++当中的内存类型不止是简单的分成
/// Stack和Heap,还有静态内存区域，即static area)
/// C++ also supports static objects
/// An object become static when static keyword is used in its declaration. See
/// the following two statements for example in C++.
/// Test t; // stack based object
/// static Test t; // Static object
// First statement when executes creates object on stack means storage is allocated on stack.
// Stack based objects are also called automatic objects or local objects. static object are
// initialized only once and live until the program terminates. Local object is created each
// time its declaration is encountered in the execution of program.
// static objects are allocated storage in static storage area. static object is destroyed
// at the termination of program. C++ supports both local static object and global static
// object
#include <iostream>

using namespace std;

class Test {
public:
    Test() {
        cout << "Create the Test instance" << endl;
    }

    ~Test() {
        cout << "destroy the Test instance" << endl;
    }
};

void myFunc() {
    static Test obj;
}

int main() {
    cout << "main() method starts" << endl;
    myFunc();
    /// 在myFunc()执行结束之后，myFunc()内部生成的Test的实例并不会调用de-constructor
    /// 只有在main()执行结束之后，myFunc()内部生成的Test的实例才会调用de-constructor
    cout << "main() method ends" << endl;
    return 1;
}