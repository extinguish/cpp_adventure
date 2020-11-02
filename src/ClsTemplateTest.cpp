//
// Created by guoshichao on 2020/8/20.
//

// the class of which using to test the class template features

#include <iostream>
#include <cstdlib>
#include <cstring>

template<typename Message>
class MessageHandler {
public:
    MessageHandler();

    ~MessageHandler();

public:
    void onInquireBasicInfo(Message *message);

    void onSetParams(Message *message);

    void onTerminalUpdatePkg(Message *message);

    void onInquireTerminalParams(Message *message);

    void onInquireSpecifiedTerminalParams(Message *rawMessage);

private:
    void test();
};

template<typename Message>
void MessageHandler<Message>::onInquireBasicInfo(Message *message) {
    std::cout << message->msgHeader.messageId << std::endl;
}

template<typename Message>
void MessageHandler<Message>::onSetParams(Message *message) {

}

template<typename Message>
void MessageHandler<Message>::onTerminalUpdatePkg(Message *message) {

}

template<typename Message>
void MessageHandler<Message>::onInquireTerminalParams(Message *message) {

}

template<typename Message>
void MessageHandler<Message>::onInquireSpecifiedTerminalParams(Message *rawMessage) {

}

template<typename Message>
MessageHandler<Message>::MessageHandler() {

}

template<typename Message>
MessageHandler<Message>::~MessageHandler() {

}

template<typename Message>
void MessageHandler<Message>::test() {

}

typedef unsigned short WORD;
typedef unsigned char BYTE;

typedef struct {
    WORD messageId;                                // 0 消息 ID
    WORD messageAttribute;                            // 2 消息体属性
    BYTE terminalPhoneNum[100];    // 5 终端手机号
    WORD messageSerialNum;                            // 11 消息流水号
    // 12 如果消息体属性中相关标识位确定消息分包处理，则该项有内容，否则无该项
    WORD packetTotalNum;                            // 13 消息总包数:该消息分包后的总包数
    WORD packetIndex;                                // 15 包序号: 从 1 开始
} JT2013MsgHeader;

typedef struct {
    JT2013MsgHeader msgHeader;
    BYTE msgBody[300]; // 消息体
    int msgBodyLen; // 消息体长度
} JT808_2013Message;

typedef struct {
    WORD messageId;                                // 0 消息 ID
    WORD messageAttribute;                            // 2 消息体属性
    BYTE protocolVersion;                        // 4版本协议
    BYTE terminalPhoneNum[20];    // 5 终端手机号
    WORD messageSerialNum;                            // 11 消息流水号
    // 12 如果消息体属性中相关标识位确定消息分包处理，则该项有内容，否则无该项
    WORD packetTotalNum;                            // 13 消息总包数:该消息分包后的总包数
    WORD packetIndex;                                // 15 包序号:从 1 开始
} JT2019MsgHeader;

typedef struct {
    JT2019MsgHeader msgHeader;
    BYTE msgBody[1024]; // 消息体
    int msgBodyLen; // 消息体长度
} JT808_2019Message;

int main(int argc, char **argv) {
    MessageHandler<JT808_2013Message> jt2013MsgHandler;
    JT808_2013Message jt2013Msg;
    memset(&jt2013Msg, 0, sizeof(JT808_2013Message));
    jt2013MsgHandler.onInquireBasicInfo(&jt2013Msg);

    MessageHandler<JT808_2019Message> jt2019MsgHandler;


}

