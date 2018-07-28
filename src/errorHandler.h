//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#ifndef DEVICE_SRC_ERRORHANDLER_H
#define DEVICE_SRC_ERRORHANDLER_H
#pragma once

#include "Arduino.h"

namespace device_lib {

enum Error{ SDBEGIN, SDAPPEND, SDDELETE, SDREAD, SDPREV };

void report_error(Error);

}
#endif //DEVICE_SRC_ERRORHANDLER_H
