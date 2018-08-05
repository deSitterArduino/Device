//**************************************************************************************************
//    sd_card.h -
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#ifndef DEVICE_SRC_RECORD_H
#define DEVICE_SRC_RECORD_H
#pragma once

#include "Arduino.h"

namespace device_lib {

struct Record
{
    Record();
    void clear_for_read();
    void clear_record();
    int _cursor = 0;    //the file cursor position for the beginning of this Record
    int _line = 0;      //the line number of this record
    int _maxLine = 0;   //the total records in the file
    String _date = "";
    String _barcode = "";

};
}
#endif //DEVICE_SRC_STRING_PAIR_H


/*type function()                                                                                  */
//
//
