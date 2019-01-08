/// a better implementation of virtual constructor
/// By delegating the object creation to class hierarchy (or
/// to a static function) we can avoid the tight coupling
/// between User and Base hierarchy
/// of which could let us abandon the tedious if-else
#include <iostream>

using namespace std;

/// Library Start
class Base {
public:
    static Base *Create(int typeId);

    Base() {}

    virtual ~Base() {}

    virtual void DisplayAction() = 0;
};

class DerivedFirst : public Base {
public:
    DerivedFirst() {
        cout << "create the DerivedFirst instance " << endl;
    }

    ~DerivedFirst() {
        cout << "Destroy the DerivedFirst instance " << endl;
    }

    void DisplayAction() {
        cout << "DerivedFirst::DisplayActions here " << endl;
    }
};

class DerivedSecond : public Base {
public:
    DerivedSecond() {
        cout << "create the DerivedSecond instance" << endl;
    }

    ~DerivedSecond() {
        cout << "destroy the DerivedSecond instance" << endl;
    }

    void DisplayAction() {
        cout << "DerivedSecond::DisplayActions here" << endl;
    }
};

class DerivedThird : public Base {
public:
    DerivedThird() {
        cout << "create the DerivedThird instance" << endl;
    }

    ~DerivedThird() {
        cout << "destroy the DerivedThird instance" << endl;
    }

    void DisplayAction() {
        cout << "DerivedThird::DisplayActions here" << endl;
    }
};

Base *Base::Create(int typeId) {
    switch (typeId) {
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
    User(int typeId) : typeId(typeId), basePtr(0) {
        basePtr = Base::Create(typeId);
    }

    ~User() {
        if (basePtr) {
            delete basePtr;
            basePtr = 0;
        }
    }

    void PerformAction() {
        if (basePtr) {
            basePtr->DisplayAction();
        } else {
            cout << "fail to create the Base Class instance" << endl;
        }
    }

private:
    Base *basePtr;
    int typeId;
};

/// 其实在这个实例当中，也是简单的使用了if-else，只是将这个if-else逻辑抽离了出来
/// 实现了一个简单的factory模式
int main() {
    int typeId;
    cout << "input the type ID(1 or 2 or 3) you want ot create ";
    cin >> typeId;

    while ((typeId != 1) && (typeId != 2) && (typeId != 3)) {
        cout << "please input the correct type ID(1 or 2 or 3)" << endl;
        cin >> typeId;
    }

    User *user = new User(typeId);
    user->PerformAction();
    delete user;

    return 1;
}























