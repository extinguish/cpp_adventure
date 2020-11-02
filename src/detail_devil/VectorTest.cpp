//
// Created by guoshichao on 20-1-14.
//

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char **argv) {
    vector<int> val;
    val.push_back(20);
    val.push_back(30);
    val.push_back(40);
    val.push_back(50);
    val.push_back(60);
    val.push_back(70);
    val.push_back(80);
    val.push_back(90);

    cout << "length " << val.size() << endl;

    for (std::vector<int>::iterator vecIter = val.begin();
         vecIter != val.end(); ) {
        int ele = *vecIter;
        if (ele == 20 || ele == 30 || ele == 50) {
            val.erase(vecIter);
            continue;
        } else {
            ++vecIter;
        }
    }
    int backElem = val.front();

    cout << "length " << val.size() << endl;
    cout << "backElem : " << backElem << endl;

}

