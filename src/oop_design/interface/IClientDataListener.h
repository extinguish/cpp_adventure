//
// Created by guoshichao on 19-1-24.
//

#ifndef CPPADVENTURE_ICLIENTDATALISTENER_H
#define CPPADVENTURE_ICLIENTDATALISTENER_H

#include <cstddef>

class IClientDataListener {
public:
    virtual void onData(void *data, size_t data_len) = 0;
};


class IAnotherDataListener {
public:
    virtual void onAnotherData(void *data, size_t data_len) = 0;

};

#endif //CPPADVENTURE_ICLIENTDATALISTENER_H
