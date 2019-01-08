//
// Created by guoshichao on 18-10-9.
//
/// demonstrate the ways to copy one vector to another vector

#include <iostream>
#include <vector>

using namespace std;

/// copy vector in iterative way
void iterative_copy_vector() {
    vector<int> int_vec = {1, 2, 3};
    vector<int> another_vec;
    for (int i = 0; i < int_vec.size(); i++) {
        another_vec.push_back(int_vec[i]);
    }

    cout << "old vector content are : " << endl;
    for (int i = 0; i < int_vec.size(); i++) {
        cout << int_vec[i] << "\t";
    }
    cout << endl;
    cout << "new vector content are " << endl;
    for (int i = 0; i < another_vec.size(); i++) {
        cout << another_vec[i] << "\t";
    }
    cout << endl;

    another_vec[1] = 100;
    cout << int_vec[1] << endl;
    cout << another_vec[1] << endl;
}

void copy_via_operator_assignment() {
    vector<int> first_vec = {1, 2, 3, 4};
    vector<int> second_vec;
    second_vec = first_vec;
    cout << "the content of the first vector are " << endl;
    for (const auto &item : first_vec) {
        cout << item << "\t";
    }
    cout << endl;
    cout << "the content of the second vector are " << endl;
    for (const auto &elem : second_vec) {
        cout << elem << "\t";
    }
    cout << endl;
    first_vec[1] = 200;

    cout << first_vec[1] << endl;
    cout << second_vec[1] << endl;
}

void copy_via_constructor() {
    vector<int> first_vector = {1, 2, 3, 4};
    vector<int> second_vector(first_vector);

    for (const auto &elem : first_vector) {
        cout << elem << "\t";
    }
    cout << endl;
    for (const auto &elem : second_vector) {
        cout << elem << "\t";
    }
    cout << endl;
}

#include <algorithm>
#include <iterator>

/// this generates a deep copy
void copy_via_builtin_func() {
    vector<int> first_vector = {1, 2, 3, 4, 5};
    vector<int> second_vector;
    copy(first_vector.begin(), first_vector.end(), back_inserter(second_vector));

    for (const auto &elem : first_vector) {
        cout << elem << "\t";
    }
    cout << endl;

    for (const auto &elem : second_vector) {
        cout << elem << "\t";
    }
    cout << endl;
}

/// this is also deep copy
void copy_via_assign_func() {
    vector<int> first_vector = {1, 2, 3, 4, 5};
    vector<int> second_vector;
    second_vector.assign(first_vector.begin(), first_vector.end());

    for (const auto &elem : first_vector) {
        cout << elem << "\t";
    }
    cout << endl;
    for (const auto &elem : second_vector) {
        cout << elem << "\t";
    }
    cout << endl;

}


int main(void) {
    iterative_copy_vector();
    copy_via_operator_assignment();
    copy_via_builtin_func();
    copy_via_assign_func();
}


