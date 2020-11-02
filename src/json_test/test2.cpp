//
// Created by guoshichao on 19-3-13.
//
// another test of json11

// the following are test data that we need to parse
// {code='null', msg='null', data={"warningState":0,"workingState":1,"ret":"1000","sb":""}}
// or
// {code='null', msg='null', data={"businessId":"dtgxfirst20181112","companyName":"KYKJ","deviceId":"866275037881621","hardwareVersion":"1.0.0","productNum":"KY-LFD","softwareVersion":"KYKJMP712E_userdebug_V1.0.8_190307","ret":"1000","sb":""}}
// or
// {code='null', msg='null', data={"DfwEnable":1,"DfwSensitivity":0,"DfwSpeed":69,"FcwEnable":1,"FcwSensitivity":1,"FcwSpeed":57,"LdwEnable":0,"LdwSensitivity":2,"LdwSpeed":96,"PcwEnable":1,"PcwSensitivity":1,"PcwSpeed":21,"debugModeSwotch":1,"ret":"1000","sb":""}}
#include "json11.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
    const char *firstRawData = "{\"warningState\":0,\"workingState\":1,\"ret\":\"1000\",\"sb\":\"\"}";
    const char *secondRawData = "{\"businessId\":\"dtgxfirst20181112\",\"companyName\":\"KYKJ\",\"deviceId\":\"866275037881621\",\"hardwareVersion\":\"1.0.0\",\"productNum\":\"KY-LFD\",\"softwareVersion\":\"KYKJMP712E_userdebug_V1.0.8_190307\",\"ret\":\"1000\",\"sb\":\"\"}";
    const char *thirdRawData = "{\"DfwEnable\":1,\"DfwSensitivity\":0,\"DfwSpeed\":69,\"FcwEnable\":1,\"FcwSensitivity\":1,\"FcwSpeed\":57,\"LdwEnable\":0,\"LdwSensitivity\":2,\"LdwSpeed\":96,\"PcwEnable\":1,\"PcwSensitivity\":1,\"PcwSpeed\":21,\"debugModeSwotch\":1,\"ret\":\"1000\",\"sb\":\"\"}";


    std::string err;
    json11::Json firstResult = json11::Json::parse(firstRawData, err);

    std::string retVal = firstResult["ret"].string_value();
    cout << "the result code are " << retVal << endl;

    std::string workingState = firstResult["workingState"].string_value();
    cout << "the workingState value are " << workingState << endl;

}

