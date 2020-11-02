//
// Created by guoshichao on 19-4-15.
//
#include <map>

#include <iostream>
#include <string>

using std::map;

template <typename T>
class ValType {
private:
    T *value;
public:
    void getValue(T *val);
};

template<typename T>
void ValType<T>::getValue(T *val) {
    this->value = val;
}

int main(int argc, char **argv) {




    return 0;
}

