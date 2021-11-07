// a simple program of which implement the sizeof operator
#include<iostream>

#define my_sizeof(x) ((char *)(&x + 1) - (char *)&x)


int main(int argc, char **argv) {
    int val = 100;
    std::cout << sizeof(val) << ", " << my_sizeof(val) << std::endl;
    return 0;
}
