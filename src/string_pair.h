//**************************************************************************************************
//    sd_card.h -
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#ifndef DEVICE_SRC_STRING_PAIR_H
#define DEVICE_SRC_STRING_PAIR_H
#pragma once

#include "Arduino.h"

namespace device_lib {

struct StringPair
{
    StringPair();
    String _date;
    String _barcode;
    
};
}
#endif //DEVICE_SRC_STRING_PAIR_H


/*type function()                                                                                  */
//
//
