//
// Created by guoshichao on 19-1-28.
//
#include <iostream>

#include <cstring>

using std::cout;
using std::cin;
using std::endl;

int DecimalToBCD(int Decimal) {
    return (((Decimal / 10) << 4) | (Decimal % 10));
}

void convertPhoneNOToBCD(char phoneBcdCode[], const char *phoneNO) {
    // the phone number are represented as char *
    // the phone number are 11 bit wide, but the
    // in this example, the phone number need to fill 0 at header
    // and keep the length as 12 bit wide.
    // for example : const char *phone_num = "013671330588";
    // we need to split the phone num into bit by bit
    const size_t phoneNumLen = strlen(phoneNO);
    char numUnit[2];
    // char bcdVal[6];
    int j = 0;
    for (int i = 0; i < phoneNumLen; i += 2) {
        numUnit[0] = phoneNO[i];
        numUnit[1] = phoneNO[i + 1];
        int decimalVal = atoi(numUnit);
        int bcdCode = DecimalToBCD(decimalVal);
        phoneBcdCode[j++] = static_cast<char>(bcdCode);
    }
    // add the end tag
    phoneBcdCode[j] = '\0';
}


int main(int argc, char **argv) {
    const char *plate = "冀A75585";
    const size_t plate_info_len = strlen(plate);
    printf("origin plate len %zu\n", plate_info_len);
    for (int i = 0; i < plate_info_len; ++i) {
        printf("%02x ", plate[i]);
    }
    printf("\n");
    unsigned char *plateNo = static_cast<unsigned char *>(malloc(plate_info_len));
    memcpy(plateNo, plate, plate_info_len);
    const size_t plateNoLen = sizeof(plateNo) / sizeof(plateNo[0]);
    printf("the plate no are %s, length are %zu\n", plateNo, plateNoLen);

    for (int i = 0; i < plate_info_len; ++i) {
        printf("%02x ", plateNo[i]);
    }
    printf("\n");

    const char *phoneNo = "020160825001";
    char phoneNoBcd[6];

    convertPhoneNOToBCD(phoneNoBcd, phoneNo);
    for (int i = 0; i < 6; i++) {
        printf("%02x ", phoneNoBcd[i]);
    }

    printf("\n");

}

