//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "errorHandler.h"

namespace device_lib {

void report_error(Error error) {
    Serial.print(F("Error ID: "));
    Serial.println(error);
}

}
