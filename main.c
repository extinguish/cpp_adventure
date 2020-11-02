#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBuf(unsigned char *buf, size_t bufLen) {
    for (int i = 0; i < bufLen; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

void parseBuffer(const unsigned char *buffer, size_t length) {
//    int begin = 0;
//    for (int i = 0; i < length;) {
//        if (buffer[i] == 0x7e) {
//            for (int msgIdx = i + 1; msgIdx < length; ++msgIdx) {
//                if (buffer[msgIdx] == 0x7e) {
//                    // this is one message that clip out
//                    int msgLen = msgIdx - i;
//
//                    i = (msgIdx + 1);
//
//                    if (msgLen != 0) {
//                        unsigned char tempBuffer[msgLen + 1];
//                        memset(tempBuffer, 0, msgLen + 1);
//                        memcpy(tempBuffer, buffer + begin, msgLen + 1);
//                        // the tempBuffer are the very buffer we need to parse out
//                        printBuf(tempBuffer, msgLen + 1);
//
//                        begin = i;
//                    }
//                    break;
//                }
//            }
//        }
//    }

    int begin = 0;
    int messageLen = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] == 0x7e) {
            messageLen = i - begin;
            if (messageLen != 0) {
                unsigned char tempBuffer[messageLen + 1];
                memset(&tempBuffer, 0, messageLen + 1);
                memcpy(&tempBuffer, buffer + begin, messageLen + 1);

                printBuf(tempBuffer, messageLen);
                printf("new message--->\n");
                begin = i + 1;
            }
        }
    }
}


int main() {

    unsigned char buf1[] = {0x7e, 0x80, 0x01, 0x00, 0x05,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x13, 0x00, 0x0e, 0x00, 0x0d,
                            0x02, 0x00, 0x00, 0xed, 0x7e,

                            0x80, 0x01, 0x00, 0x05,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x13, 0x00, 0x0f, 0x00, 0x0e,
                            0x00, 0x02, 0x00, 0xef,

                            0x80, 0x01, 0x00, 0x05,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x13, 0x00, 0x10, 0x00, 0x0e,
                            0x00, 0x02, 0x00, 0xff,

                            0x80, 0x01, 0x00, 0x05,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x13, 0x00, 0x0f, 0x00, 0x0e,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x01, 0x59, 0x06, 0x25, 0x00,
                            0x00, 0x02, 0x00, 0xef, 0x7e};

    const size_t buf1Len = sizeof(buf1);

    unsigned char buf[] = {0x7e, 0x80, 0x01, 0x00, 0x05,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x13, 0x00, 0x0e, 0x00, 0x0d,
                           0x02, 0x00, 0x00, 0xed, 0x7e,

                           0x7e, 0x80, 0x01, 0x00, 0x05,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x13, 0x00, 0x0f, 0x00, 0x0e,
                           0x00, 0x02, 0x00, 0xef, 0x7e,

                           0x7e, 0x80, 0x01, 0x00, 0x05,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x13, 0x00, 0x10, 0x00, 0x0e,
                           0x00, 0x02, 0x00, 0xff, 0x7e,

                           0x7e, 0x80, 0x01, 0x00, 0x05,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x13, 0x00, 0x0f, 0x00, 0x0e,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x01, 0x59, 0x06, 0x25, 0x00,
                           0x00, 0x02, 0x00, 0xef, 0x7e};
    const size_t len = sizeof(buf);

    parseBuffer(buf, len);
//    parseBuffer(buf1, buf1Len);

    if (0) {
        int begin = 0;
        printf("%zu \n", len);
        for (int i = 0; i < len;) {
            if (buf[i] == 0x7e) {
                printf("start of message\n");
                printf("%02x ", buf[i]);
                for (int j = i + 1; j < len; ++j) {
                    printf("%02x ", buf[j]);
                    if (buf[j] == 0x7e) {
                        // this is one message that clip out
                        int msgLen = j - i + 1;
                        printf("\nbegin index are --> %d\n", begin);
                        // record the stamp length
                        printf("--->j = %d\n", j);
                        i = (j + 1);
                        printf("---> i = %d \n", i);
                        printf("\nend of message with length of %d\n", msgLen);
                        begin = i;

                        break;
                    }
                }
            }
        }
    }


    return 0;
}