//
// Created by guoshichao on 19-5-10.
//

#include <iostream>
#include <list>

using namespace std;

typedef struct {
    int x;
    int y;
} ElemTest;

int main(int argc, char **argv) {
    // initializing list of integers
    list<int> list1 = {10, 15, 20, 25, 30, 35};

    // declaring list iterators
    list<int>::iterator it = list1.begin();
    list<int>::iterator it1 = list1.begin();

    // incrementing the positions of iterators
    advance(it, 2);
    advance(it1, 5);

    // printing original list
    cout << "The original list is : ";
    for (list<int>::iterator i = list1.begin(); i != list1.end(); i++)
        cout << *i << " ";

    cout << endl;

    // using erase() to erase single element
    // erases 20
    list1.erase(it);

    // list after deletion 1 element
    cout << "The list after deleting 1 element using erase() : ";
    for (list<int>::iterator i = list1.begin(); i != list1.end(); i++)
        cout << *i << " ";

    cout << endl;

    it = list1.begin();

    // incrementing the positions of iterators
    advance(it, 2);

    // using erase() to erase multiple elements
    // erases 25,30
    list1.erase(it, it1);

    // list after deletion of multiple elements
    cout << "The list after deleting multiple elements using erase() : ";
    for (list<int>::iterator i = list1.begin(); i != list1.end(); i++)
        cout << *i << " ";

    cout << endl;

    list<ElemTest *> elemList;
    ElemTest *first = static_cast<ElemTest *>(malloc(sizeof(ElemTest)));
    ElemTest *second = static_cast<ElemTest *>(malloc(sizeof(ElemTest)));
    first->x = 100;
    first->y = 200;
    elemList.push_back(first);
    second->x = 300;
    second->y = 400;
    elemList.push_back(second);
//    elemList.push_back(second);
//    elemList.push_back(second);
//    elemList.push_back(second);
//    elemList.push_back(second);

    cout << "---------------------------------------" << endl;

    for (list<ElemTest *>::iterator elIt = elemList.begin(); elIt != elemList.end(); ) {
        ElemTest *elemTest = *elIt;
        cout << "x = " << elemTest->x << endl;

        elemList.erase(elIt);
        ++elIt;
    }
//    cout << "list size are " << elemList.size() << endl;








}


