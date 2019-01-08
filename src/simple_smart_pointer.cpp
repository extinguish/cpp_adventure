/// create a smart pointer by manual
/// In fact, smart pointers are objects which store pointers to dynamically allocated objects.
// 以下就是我们手动创建的一个简单的智能指针:(这个智能指针很简单，但是实现了自动管理实例的分配和释放的过程，
// 即已经满足了智能指针的定义，只是这个指针不是通用的类似于smart_ptr那样强大，但是实现了基本概念)

#include <iostream>

using namespace std;

class SimpleCar {
public:
    void run() {
        cout << "Car running... " << endl;
    }
};


/// smart pointer for class SimpleCar
class SimpleCarSmartPointer {
public:
    SimpleCarSmartPointer(SimpleCar *car) : car(car) {

    }

    ~SimpleCarSmartPointer() {
        cout << "deleting dynamically allocated SimpleCar instance" << endl;
        delete car;
    }

    SimpleCar *operator->() {
        return car;
    }

private:
    SimpleCar *car;
};

int main() {
    SimpleCarSmartPointer simpleCarPointer(new SimpleCar());
    simpleCarPointer->run();
    return 1;
}

