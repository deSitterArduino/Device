//**************************************************************************************************
//    sd_card.cpp -
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "record.h"

namespace device_lib {

Record::Record()
{
}

void Record::clear_for_read() {
    _date = "";
    _barcode = "";
}

void Record::clear_record() {
    _date = "";
    _barcode = "";
    _cursor = 0;
    _line = 0;
    _maxLine = 0;
}

}
