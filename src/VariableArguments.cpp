//
// Created by guoshichao on 19-4-4.
//

#include <iostream>
#include <cstdarg>

using std::cin;
using std::cout;
using std::endl;

// a program of which using to demonstrate the variable arguments in c++
// just like java's:
// void main(String... args) {} method

void simple_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0') {
        if (*fmt == 'd') {
            int i = va_arg(args, int);
            cout << i << endl;
        } else if (*fmt == 'c') {
            int c = va_arg(args, int);
            cout << static_cast<char>(c) << endl;
        } else if (*fmt == 'f') {
            double d = va_arg(args, double);
            cout << d << endl;
        }
        ++fmt;
    }
    va_end(args);
}

template<class T>
void func2(bool separate, std::initializer_list<T> list) {
    for (auto elem : list) {
        std::cout << elem << std::endl;
    }
}

int findMax(int n, ...) {
    int i, val, largest;
    va_list vl;
    va_start(vl, n);
    largest = va_arg(vl, int);
    for (i = 1; i < n; ++i) {
        val = va_arg(vl, int);
        largest = (largest > val) ? largest : val;
    }
    va_end(vl);
    return largest;
}

void findExtraVal(bool hasExtra, ...) {
    if (hasExtra) {
        va_list vl;
        va_start(vl, nullptr);
        int firstExtraVal = va_arg(vl, int);
        int secondExtraVal = va_arg(vl, int);
        va_end(vl);

        cout << "the first extra value are " << firstExtraVal << ", the second extra value are " << secondExtraVal << endl;
    } else {
        cout << "no extra value provided" << endl;
    }
}


int main(int argc, char **argv) {
    simple_print("dcff", 3, 'a', 1.999, 34.2);

    // process_multiple_args(true, 100, 200);

    func2(false, {100, 200});

    int maxVal = findMax(3, 1, 50, 30);
    cout << "the max val are " << maxVal << endl;
    findMax(0);

    findExtraVal(true, -500, -900);
    findExtraVal(false);
}

