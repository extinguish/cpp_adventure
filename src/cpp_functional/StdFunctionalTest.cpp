//
// Created by guoshichao on 19-1-27.
//

// adventure of the std::function
#include <functional>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct Foo {
    Foo(int num) : _num(num) {}

    void print_add(int i) const {
        cout << _num + i << endl;
    };

    int _num;
};

void print_num(int i) {
    cout << "the value of i are " << i << endl;
}

struct PrintNum {
    void operator()(int i) const {
        cout << " the value of i" << i << endl;
    }
};

class Test {
public:
    void init();

public:
    void test(int val);

public:
    std::function<void(Test &, int)> test_func;

};

void Test::test(int val) {
    cout << "current test" << val << endl;
}

void Test::init() {
    test_func = &Test::test;
    // test_func(&this, 10);
}

int main() {
    // store a free function
    std::function<void(int)> f_display = print_num;

    f_display(-9);

    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();

    // store the result of a call to std::bind
    std::function<void()> f_display_43 = std::bind(print_num, 43);
    f_display_43();

    // store a call to a member function
    std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
    const Foo foo(100);
    f_add_display(foo, 1);
    f_add_display(foo, 100);


    Test test;
    test.init();

    std::function<void(Test &, int)> test_function = &Test::test;

    test_function(test, 100);


}

