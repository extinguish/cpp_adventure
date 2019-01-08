//
// Created by guoshichao on 18-9-30.
//
/// Nested list in C++ STL
/// we need to create the following form of nested list
/// Input :  Number of lists: 2
/// 1st list: {1 2}
/// 2nd list:  {3 4 5 6
/// Output :
/// [
///   [ 1  2 ]
///   [ 3  4  5  6 ]
/// ]
///
/// Input : Number of lists: 3
/// 1st list : {0 1}
/// 2nd list : {1 2 3}
/// 3rd list : {2 3 4 5}
/// Output :
/// [
///   [ 0  1 ]
///   [ 1  2  3 ]
///   [ 2  3  4  5 ]
/// ]
#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void print_nested_list(list<list<int>> nested_list) {
    cout << "the content of this nested list are : " << endl;
    cout << "[ " << endl;
    list < list < int >> ::iterator
    nested_iterator;
    for (nested_iterator = nested_list.begin(); nested_iterator != nested_list.end();
         ++nested_iterator) {
        cout << "\t[\t";
        list<int>::iterator sub_list_iterator;
        list<int> &sub_list_ptr = *nested_iterator;

        for (sub_list_iterator = sub_list_ptr.begin(); sub_list_iterator != sub_list_ptr.end();
             ++sub_list_iterator) {
            cout << *sub_list_iterator << "\t";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

void test_nested_list() {
    list <list<int>> nested_list;
    list<int> sub_list;
    // the nested level
    int n;
    // the sub list size
    int m;
    // the total number of elements inside the nested list
    int num;
    n = 3;

    for (int i = 0; i < n; ++i) {
        m = i + 2;
        for (int j = 0; j < m; ++j) {
            num = i + j;
            sub_list.push_back(num);
        }
        nested_list.push_back(sub_list);
        // erase the elements inside the sub list,
        // thus the sub list can be used for next loop
        sub_list.erase(sub_list.begin(), sub_list.end());
    }

    print_nested_list(nested_list);
}

int main() {
    test_nested_list();

    return 1;
}

