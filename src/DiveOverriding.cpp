//
// Created by guoshichao on 2020/3/24.
//
#include <iostream>

using namespace std;

class A {
public:
    virtual void f() = 0;
};


class B : public A {
private:
    virtual void f() {
        cout << "B::f()" << endl;
    }
};


class C : public B {
protected:
    virtual void f() {
        cout << "C::f()" << endl;
    }
};

int main(int argc, char **argv) {
    B *b = new B();

    C *c = new C();

    A *a1 = b;
    a1->f();
    A *a2 = c;
    a2->f();

    return 0;
}
