// the program of which using to test the std::function feature 
#include<iostream>
#include<functional>

typedef std::function<int(int, int)> com_func;

int add(int x, int y) {
    return x + y;
}

auto mod = [](int a, int b){return a % b;};

class divide {
public:
    int operator()(int x, int y) {
        return x / y;
    }
};

int main(int argc, char **argv) {
    com_func a = add;
    com_func m = mod;
    com_func d = divide();
    std::cout << a(3, 4) << std::endl;
    std::cout << m(10, 2) << std::endl;
    std::cout << d(9, 3) << std::endl;
    return 0;
}