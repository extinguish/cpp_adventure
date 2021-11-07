// the following program are using to demonstrate the std::bind
#include<functional>
#include<iostream>

// 可将std::bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。
// std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以使用std::function保存。std::bind主要有以下两个作用：
// 将可调用对象和其参数绑定成一个防函数；
// 只绑定部分参数，减少可调用对象传入的参数。

double divide_func(int a, int b) {
    return a / b;
}

// bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
// 必须显示的指定&Foo::print_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Foo::print_sum前添加&；
// 使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址 &foo；
class Foo {
public:
    void print_num(int n1, int n2) {
        std::cout << n1 + n2 << std::endl;
    }
    int data = 10;
};



int main(int argc, char **argv) {
    auto func_handler = std::bind(divide_func, std::placeholders::_1, 2);

    std::cout << func_handler(10) << std::endl;

    std::cout << "start to test the func of bind to class internal member" << std::endl;
    Foo foo;
    auto foo_handler = std::bind(&Foo::print_num, &foo, 100, std::placeholders::_1);
    foo_handler(200);

    return 0;
}

// 关于std::bind的内部实现原理的话，可以参考这里：https://www.cnblogs.com/xusd-null/p/3698969.html