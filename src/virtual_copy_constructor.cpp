//
// Created by guoshichao on 18-9-29.
//
// 之前我们通过virtual constructor实现了在运行时当中动态的指定要创建的实例的类型
// 那么问题来了:Is it possible to create an object without knowing it’s exact class type?
// 可以通过virtual copy constructor来实现
// Sometimes we may need to construct an object from another existing object. Precisely
// the copy constructor does the same. The initial state of new object will be based on
// another existing object state. The compiler places call to copy constructor when an
// object being instantiated from another object. However, the compiler needs concrete
// type information to invoke appropriate copy constructor.
#include <iostream>

using namespace std;

class Base {
public:
    Base() {}

    virtual ~Base() {}

    virtual void changeAttributes() = 0;

    static Base *create(int id);

    virtual Base *clone() = 0;
};

class DerivedFirst : public Base {
public:
    DerivedFirst() {
        cout << "Derived first created" << endl;
    }

    DerivedFirst(const DerivedFirst &other) {
        cout << "Derived first copy constructor is called" << endl;
    }

    ~DerivedFirst() {
        cout << "Derived first instance is destroyed" << endl;
    }

    void changeAttributes() {
        cout << "Derived first change attributes" << endl;
    }

    Base *clone() {
        return new DerivedFirst(*this);
    }
};

class DerivedSecond : public Base {
public:
    DerivedSecond() {
        cout << "Derived second created" << endl;
    }

    DerivedSecond(const DerivedSecond &other) {
        cout << "Derived second copy constructor is called" << endl;
    }

    ~DerivedSecond() {
        cout << "Derived second instance is destroyed" << endl;
    }

    void changeAttributes() {
        cout << "Derived second change attributes" << endl;
    }

    Base *clone() {
        return new DerivedSecond(*this);
    }
};

class DerivedThird : public Base {
public:
    DerivedThird() {
        cout << "Derived Third instance created " << endl;
    }

    DerivedThird(const DerivedThird &another) {
        cout << "Derived Third copy constructor invoked" << endl;
    }

    ~DerivedThird() {
        cout << "Derived Third instance destroyed" << endl;
    }

    void changeAttributes() {
        cout << "Derived Third change attributes" << endl;
    }

    Base *clone() {
        return new DerivedThird(*this);
    }
};

Base *Base::create(int id) {
    switch (id) {
        case 1:
            return new DerivedFirst;
        case 2:
            return new DerivedSecond;
        case 3:
            return new DerivedThird;
    }
    return nullptr;
}

class User {
public:
    User() : ptr(0) {
        int input;
        cout << "input the type you want to create" << endl;
        cin >> input;
        while ((input != 1) && (input != 2) && (input != 3)) {
            cout << "please input the correct type" << endl;
            cin >> input;
        }

        ptr = Base::create(input);
    }

    ~User() {
        if (ptr) {
            delete ptr;
            ptr = 0;
        }
    }

    void action() {
        Base *newPtr = ptr->clone();
        newPtr->changeAttributes();
        delete newPtr;
    }

private:
    Base *ptr;
};

int main() {
    User *user = new User();
    user->action();

    delete user;
    return 1;
}


