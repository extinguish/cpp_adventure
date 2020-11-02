//
// Created by guoshichao on 19-1-30.
//
/// test the nest class features

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class OutCls {
public:

    int x;
public:
    class NestFirstCls {

    };

public:
    class NestSecondCls {
    public:
        void handleAction(OutCls *outCls);
    };


};

void OutCls::NestSecondCls::handleAction(OutCls *outCls) {
    outCls->x = 100;
    cout << outCls->x << endl;
}


int main(int argc, char **argv) {
    OutCls outCls;
    OutCls::NestSecondCls secondCls;
    secondCls.handleAction(&outCls);

}


