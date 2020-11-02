//
// Created by guoshichao on 19-1-27.
//
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

void decimalToHex(char *hexVal, int decimalVal) {
    char val[2];
    // counter for hexadecimal number array
    int i = 0;
    while (decimalVal != 0) {
        // temporary variable to store remainder
        int temp = 0;

        // storing remainder in temp variable.
        temp = decimalVal % 16;

        // check if temp < 10
        if (temp < 10) {
            val[i] = temp + 48;
            i++;
        } else {
            val[i] = temp + 55;
            i++;
        }
        decimalVal = decimalVal / 16;
    }
    val[i] = '\0';

    // printing hexadecimal number array in reverse order
    for (int j = i - 1, index = 0; j >= 0; j--, index++) {
        hexVal[index] = val[j];
    }
}

void getTimeInBcd(char bcdVal[]) {
    // get system date and time
    time_t current_time = time(NULL);
    struct tm timeVal = *localtime(&current_time);

    printf("now %d-%d-%d %d:%d:%d\n", timeVal.tm_year + 1900,
           timeVal.tm_mon + 1, timeVal.tm_mday,
           timeVal.tm_hour, timeVal.tm_min, timeVal.tm_sec);

    const int year = timeVal.tm_year + 1900;
    const int yearWant =
            year % 2000; // if the year are 2019, then what we truly need are 19(just the last two bit are need)
    const int month = timeVal.tm_mon + 1;
    const int day = timeVal.tm_mday;
    const int hour = timeVal.tm_hour;
    const int minute = timeVal.tm_min;
    const int second = timeVal.tm_sec;
    char *test = static_cast<char *>(malloc(2));
    memset(test, 0, 2);
    decimalToHex(test, yearWant);
    bcdVal[0] = static_cast<char>(atoi(test));
    printf("year are %d \n", bcdVal[0]);

    memset(test, 0, 2);
    decimalToHex(test, month);
    bcdVal[1] = static_cast<char>(atoi(test));
    printf("month are origin : %s, converted %d \n", test, bcdVal[1]);

    decimalToHex(test, day);
    bcdVal[2] = static_cast<char>(atoi(test));
    printf("day are origin : %s, converted %d \n", test, bcdVal[2]);

    memset(test, 0, 2);
    decimalToHex(test, hour);
    bcdVal[3] = static_cast<char>(atoi(test));
    printf("hour are %d \n", bcdVal[3]);

    memset(test, 0, 2);
    decimalToHex(test, minute);
    bcdVal[4] = static_cast<char>(atoi(test));
    printf("minute are %d \n", bcdVal[4]);

    memset(test, 0, 2);
    decimalToHex(test, second);
    bcdVal[5] = static_cast<char>(atoi(test));
    printf("second are %d \n", bcdVal[5]);

}

int main(int argc, char **argv) {
    char bcdVal[6] = {0};
    getTimeInBcd(bcdVal);


    for (int i = 0; i < 6; ++i) {
        printf("%d ", bcdVal[i]);
    }
    printf("\n");
}

