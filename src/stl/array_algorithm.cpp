//
// Created by guoshichao on 18-9-30.
//
/// the algorithm that provided inside std::array
/// 这里涉及到的所有的算法大部分都是结合lambda表达式来进行实现的
/// 因此我们可以将这里所涉及到的所有的算法都理解成类似于Java当中的Stream操作一样，
/// 这里的算法就是Stream上提供的操作符.
#include <iostream>
#include <algorithm>

using namespace std;

/// all_of() function:
/// This function operates on whole range of array elements and can save
/// time to run a loop to check each elements one by one. It checks for
/// a given property on every element and returns true when each element
/// in range satisfies specified property, else returns false.
void test_all_of() {
    cout << "input the elements you want to init : ";
    int num_elems;
    cin >> num_elems;
    int arr[num_elems];
    int current_num = 0;
    while (current_num < num_elems) {
        int val;
        cin >> val;
        arr[current_num] = val;
        ++current_num;
    }
    cout << "the array you constructed are : " << endl;
    for (int i = 0; i < num_elems; i++) {
        cout << arr[i] << '\t';
    }
    cout << endl;


}


int main() {
    test_all_of();

    return 1;
}


