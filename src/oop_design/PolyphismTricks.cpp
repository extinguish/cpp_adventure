//
// Created by guoshichao on 19-1-8.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Parent {
public:
    virtual void name() {
        cout << "Parent Name : china" << endl;
    }

    virtual void personalInfo() {
        name();
        cout << "Parent information" << endl;
    }
};

class Child : public Parent {
public:
    virtual void name() {
        cout << "Child name : Beijing " << endl;
    }

    virtual void personalInfo() {
        name();
        cout << "Child Information " << endl;
    }
};

int main() {
    Parent *parent = new Child;
    parent->personalInfo();
    delete parent;
    return 0;
}

