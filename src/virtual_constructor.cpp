// virtual constructor
// Can we make a class constructor virtual in C++ to create polymorphic objects?
// No. C++ being static typed (the purpose of RTTI is different) language, it is
// meaningless to the C++ compiler to create an object polymorphically. The compiler
// must be aware of the class type to create the object. In other words, what type
// of object to be created is a compile time decision from C++ compiler perspective. If
// we make constructor virtual, compiler flags an error. In fact except inline,
// no other keyword is allowed in the declaration of constructor.
//
// In practical scenarios we would need to create a derived class object in a class
// hierarchy based on some input. Putting in other words, object creation and object
// type are tightly coupled which forces modifications to extended. The objective of
// virtual constructor is to decouple object creation from it’s type.
//
// How can we create required type of object at runtime?
#include <iostream>

using namespace std;

/// library start
class Base {
public:
    Base() {

    }

    virtual ~Base() {}

    virtual void DisplayAction() = 0;
};

class DerivedFirst : public Base {
public:
    DerivedFirst() {
        cout << "DerivedFirst created" << endl;
    }

    ~DerivedFirst() {
        cout << "DerivedFirst destroyed" << endl;
    }

    void DisplayAction() {
        cout << "DerivedFirst::DisplayAction called" << endl;
    }
};

class DerivedSecond : public Base {
public:
    DerivedSecond() {
        cout << "DerivedSecond created" << endl;
    }

    ~DerivedSecond() {
        cout << "DerivedSecond destroyed" << endl;
    }

    void DisplayAction() {
        cout << "DerivedSecond::DisplayAction called" << endl;
    }
};
/// Library End


class User {
public:
    User() : pBase(0) {
        // 如果我们想要在运行时根据用户输入，动态的决定是要创建DerivedFirst还是DerivedSecond的话,怎么实现?
        // 当然简单的方法，就是使用if-else来进行判断
        // 以下就是具体的实现:
        int input;
        cout << "Enter the ID (1 or 2) you want to init";
        cin >> input;
        while ((input != 1) && (input != 2)) {
            cout << "Enter 1 or 2" << endl;
            cin >> input;
        }

        if (input == 1) {
            pBase = new DerivedFirst;
        } else {
            pBase = new DerivedSecond;
        }
    }

    ~User() {
        if (pBase) {
            delete pBase;
            pBase = 0;
        }
    }

    void Action() {
        pBase->DisplayAction();
    }

private:
    Base *pBase;
};

/// User的实现比较原始，即直接使用if-else来手动进行判断想要创建的类型
/// 但是如果Base新增加了一种子类型，我们应该怎么做，继续扩展User类的
/// if-else判断吗? 应该有一种更好的实现
int main() {
    User *user = new User();

    user->Action();
    delete user;
    return 1;
}