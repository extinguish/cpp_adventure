//
// Created by guoshichao on 18-9-30.
//
/// evaluate the "std list"
/// Functions used with List :
/// front() – Returns the value of the first element in the list
/// back() – Returns the value of the last element in the list
/// push_front(g) – Adds a new element ‘g’ at the beginning of the list
/// push_back(g) – Adds a new element ‘g’ at the end of the list
/// pop_front() – Removes the first element of the list, and reduces size of the list by 1
/// pop_back() – Removes the last element of the list, and reduces size of the list by 1
/// begin() – Returns an iterator pointing to the first element of the list
/// end() – Returns an iterator pointing to the theoretical last element which follows the last element
/// empty() – Returns whether the list is empty(1) or not(0)
/// insert() – Inserts new elements in the list before the element at a specified position
/// erase() – Removes a single element or a range of elements from the list
/// assign() – Assigns new elements to list by replacing current elements and resizes the list
/// remove() – Removes all the elements from the list, which are equal to given element
/// reverse() – Reverses the list
/// size() – Returns the number of elements in the list
/// sort() – Sorts the list in increasing order

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void show_list(list<int> target_list) {
    list<int>::iterator list_iterator;
    for (list_iterator = target_list.begin(); list_iterator != target_list.end(); ++list_iterator) {
        cout << '\t' << *list_iterator;
    }
    cout << endl;
}

void test_list_op() {
    list<int> test_list_1, test_list_2;
    for (int i = 0; i < 10; ++i) {
        test_list_1.push_back(i * 2);
        test_list_2.push_back(i * 3);
    }

    cout << "print out the first list : " << endl;
    show_list(test_list_1);

    cout << "print out the second list : " << endl;
    show_list(test_list_2);

    cout << "the first list inside the first list are " << test_list_1.front() << endl;
    cout << "the last list inside the first list are " << test_list_1.back() << endl;

    test_list_1.pop_front();
    cout << "after pop up the first element inside the first list " << endl;
    show_list(test_list_1);

    int new_val;
    cout << "insert a new value into the first list " << endl;
    cin >> new_val;
    test_list_1.push_back(new_val);
    cout << "then the first list content are " << endl;
    show_list(test_list_1);

    test_list_1.reverse();
    cout << "reverse the first list " << endl;
    show_list(test_list_1);
    test_list_1.clear();
}

///  g++ -std=c++11 -o list_operation list_operation.cpp
int main() {
    test_list_op();
    return 1;
}











