//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_RESPONSEHANDLER_H
#define CPPADVENTURE_RESPONSEHANDLER_H

#include "IClientDataListener.h"

#include <stddef.h>
#include <iostream>

using std::cout;
using std::endl;

class ResponseHandler : public IClientDataListener {
public:
    void processData(void *data, size_t len);

    void onData(void *data, size_t data_len);
};

class AnotherResponseHandler : public IClientDataListener, IAnotherDataListener {
public :
    void onData(void *data, size_t data_len);

    void onAnotherData(void *data, size_t data_len);

};

// the ThirdResponseHandler are different with AnotherResponseHandler
class ThirdResponseHandler : public IClientDataListener, public IAnotherDataListener {
public:
    void onData(void *data, size_t data_len);

    void onAnotherData(void *data, size_t data_len);
};

#endif //CPPADVENTURE_RESPONSEHANDLER_H
