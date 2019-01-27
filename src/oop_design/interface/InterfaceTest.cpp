//
// Created by guoshichao on 19-1-24.
//
#include "IClientDataListener.h"
#include "ResponseHandler.h"

class ClientUser {
public:
    void setOnClientDataListener(IClientDataListener *listener);

private:
    IClientDataListener *listener;

};

void ClientUser::setOnClientDataListener(IClientDataListener *listener) {
    this->listener = listener;
}


int main(int argc, char **argv) {
    ClientUser clientUser;
    ResponseHandler responseHandler;

    clientUser.setOnClientDataListener(&responseHandler);

}

