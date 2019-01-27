//
// Created by guoshichao on 19-1-24.
//

#include <cstring>
#include "Thread.h"
#include "log.h"
#include <unistd.h>
#include <cstdlib>

using adasplus::Message;

class IResponseListener {
public:
    virtual void onResponse(adasplus::Message *message) = 0;
};

class IClientDataListener {
public:
    virtual void onClientData(unsigned char *data, size_t length) = 0;
};

class ResponseHandler : public adasplus::Thread, public IClientDataListener {
public:
    ResponseHandler();

    ~ResponseHandler();

    void setResponseListener(IResponseListener *listener) { mListener = listener; }

    void response(int fd, void *data, size_t size);

public:
    // implemented from IClientDataListener interface
    void onClientData(unsigned char *data, size_t length);

protected:
    // implemented from Thread
    virtual int32_t processData(adasplus::Message *message);

private:
    IResponseListener *mListener;

};

class Client {

public:
    Client();

    ~Client();

    void setOnClientDataListener(IClientDataListener *dataListener);

    void writeDataToServer(void *data, size_t dataLen);

private:
    IClientDataListener *dataListener;

};

void Client::setOnClientDataListener(IClientDataListener *dataListener) {
    this->dataListener = dataListener;
}

Client::Client() {
}

Client::~Client() {
}

void Client::writeDataToServer(void *data, size_t dataLen) {
    if (this->dataListener != nullptr) {
        LOGD("notify the data listener to write data\n");
        this->dataListener->onClientData(static_cast<unsigned char *>(data), dataLen);
    } else {
        LOGD("the data listener do not setup\n");
    }
}

ResponseHandler::ResponseHandler() {

}

ResponseHandler::~ResponseHandler() {

}

void ResponseHandler::response(int fd, void *data, size_t size) {
    LOGD("encapsulate the raw data with message object\n");
    Message *msgToProcess = static_cast<Message *>(malloc(sizeof(Message)));
    msgToProcess->dataLen = size;
    msgToProcess->dataPtr = malloc(size);
    memcpy(msgToProcess->dataPtr, data, size);
    LOGD("start process data notify\n");
    adasplus::Thread::processDataNotify(msgToProcess);
}

void ResponseHandler::onClientData(unsigned char *data, size_t length) {
    LOGD("received the client data with length of %d\n", length);
    response(-1, data, length);
}

int32_t ResponseHandler::processData(adasplus::Message *message) {
    LOGD("start truly process the data of \"%s\"\n", static_cast<char *>(message->dataPtr));
    return 0;
}

class ResponseProcessor : public IResponseListener {
public:
    ResponseProcessor();

    ~ResponseProcessor();

public:
    void onResponse(adasplus::Message *message);
};

void ResponseProcessor::onResponse(adasplus::Message *message) {
    LOGD("the final place, to process the message with length of %zu\n", message->dataLen);
}

ResponseProcessor::ResponseProcessor() {
}

ResponseProcessor::~ResponseProcessor() {
}


int main(int argc, char **argv) {
    // test the adasplus concurrent utils
    ResponseProcessor responseProcessor;
    ResponseHandler responseHandler;
    responseHandler.setResponseListener(&responseProcessor);
    responseHandler.start();
    Client client;
    client.setOnClientDataListener(&responseHandler);
    const char *data = "Adasplus - KyLab";
    const size_t dataLen = strlen(data);
    for (int i = 0; i < 10; ++i) {
        LOGD("the data to send to server are %s, with length are %zu\n", data, dataLen);
        client.writeDataToServer((void *) data, dataLen);
        sleep(2); // sleep 2 seconds and send data later
    }
}

