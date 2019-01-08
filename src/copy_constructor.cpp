// 用于分析"赋值构造函数"和"拷贝构造函数"的调用时机
#include <iostream>
#include <stdio.h>

using namespace std;

class TestCopyBehavior {
public:
    TestCopyBehavior() {}

    TestCopyBehavior(const TestCopyBehavior &other) {
        cout << "Copy constructor method invoked" << endl;
    }

    TestCopyBehavior &operator=(TestCopyBehavior &other) {
        cout << "assignment operator method invoked" << endl;
    }
};

int main() {
    TestCopyBehavior firstTest, secondTest;
    secondTest = firstTest; // assignment operator method is called (这个过程没有新的实例被创建)
    TestCopyBehavior thirdTest = firstTest;// copy constructor is called (这个过程有新的实例被创建)
    getchar();
    return 1;
}

// 关于以上代码的解释:
// Copy constructor is called when a new object is created from an existing object,
// as a copy of the existing object (see this G-Fact). And assignment operator is
// called when an already initialized object is assigned a new value from another
// existing object.
// t2 = t1;  // calls assignment operator, same as "t2.operator=(t1);"
// Test t3 = t1;  // calls copy constructor, same as "Test t3(t1);"
