#include <cstdlib>
#include <cstring>

#include <iostream>

using std::cout;
using std::endl;
//
// Created by guoshichao on 19-1-24.
//
typedef unsigned char BYTE;

void arrayProcess(char arr[]) {
    const char* test = "the best wishes";
    memcpy(arr, test, strlen(test));

    arr[strlen(test)] = '\0';
}

int main(int argc, char **argv) {

    BYTE *first_val;

    const char *value = "cpp_type_conversion";

    first_val = static_cast<BYTE *>(malloc(strlen(value)));
    memcpy(first_val, value, strlen(value));

    cout << "the length of the first value : " << strlen(reinterpret_cast<const char *>(first_val)) << endl;
    cout << "the length of the vale are : " << strlen(value) << endl;
    cout << "using sizeof to calculate : " << sizeof(first_val) << endl;
    // we cannot use the static_cast<char *> to convert "unsigned char*" to "char*"
    cout << "the length of the first value --> " << strlen((char *) first_val) << endl;
    // cout << "another way to calculate the first value " << strlen(static_cast<char *>(first_val)) << endl;

    char arr[100];
    arrayProcess(arr);
    printf("the content of arr are \"%s\"\n", arr);
}
