//
// Created by guoshichao on 19-1-24.
//


#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

void decToHexa(char hexVal[], int n) {
    char val[2];
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            val[i] = temp + 48;
            i++;
        } else {
            val[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
    val[i] = '\0';

    // printing hexadecimal number array in reverse order
    for (int j = i - 1, index = 0; j >= 0; j--, index++) {
        hexVal[index] = val[j];
    }
}

// the BCD value are represented as 0000 0001
// and we could convert the BCD value to hex value format
// so the BCD code could represented as hex code

// convert phone number to bcd code
int main(int argc, char **argv) {
    // the phone number are represented as char *
    // the phone number are 11 bit wide, but the
    // in this example, the phone number need to fill 0 at header
    // and keep the length as 12 bit wide.
    const char *phone_num = "013671330588";
    // we need to split the phone num into bit by bit
    const size_t phoneNumLen = strlen(phone_num);
    char numUnit[2];
    char bcdVal[6];
    int j = 0;
    for (int i = 0; i < phoneNumLen; i += 2) {
        numUnit[0] = phone_num[i];
        numUnit[1] = phone_num[i + 1];
        int decimalVal = atoi(numUnit);
        printf("the value are %d\n", decimalVal);
        // now convert the decimalVal to the binary format
        // convertDecimalToHex(decimalVal);
        char *val;
        val = static_cast<char *>(malloc(2));
        decToHexa(val, decimalVal);
        printf("---> value are %s\n", val);
        cout << atoi(val) << endl;
        bcdVal[j++] = atoi(val);
        free(val);
    }

    for (int i = 0; i < 6; i++) {
        printf("%d ", bcdVal[i]);
    }
    printf("\n");
}
