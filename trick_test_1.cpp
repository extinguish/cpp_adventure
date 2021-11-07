// 这个类用于分析浮点数的特性
// 即我们要在c++当中判断两个浮点数是否相等 -> 这个是个坑
#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>

struct TestStruct {
    char a;
    short b;
    int c;
    char d;
};

struct TestStruct1 {
    char a;
    short b;
    int c;
    char d;
    short e;
};

int main(int argc, char **argv) {
    double first_num = 1.0000000000000000001;
    double second_num = 1.000000000000000002;
    if (first_num == second_num) {
        std::cout << "the first num equals with second num" << std::endl;
    } else {
        std::cout << "the first num DO NOT EQUALS with second num" << std::endl;
    }
    const double eps = 1.0e-9;
    if (std::fabs(first_num - second_num) <= eps) {
        
    }

    struct TestStruct test;
    size_t struct_size = sizeof(test);
    
    std::cout << "struct size are " << struct_size << "a:" << sizeof(test.a) << ", b:" << sizeof(test.b) << ", c" << sizeof(test.c) << ", d" << sizeof(test.d)<< std::endl;


    struct TestStruct1 test1;
    size_t struct_size1 = sizeof(test1);
    std::cout << "struct size_1 are " << struct_size1 << std::endl;

    return 0;
}