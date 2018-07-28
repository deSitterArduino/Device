//**************************************************************************************************
//    sd_card.h -
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#ifndef DEVICE_SRC_SD_CARD_H
#define DEVICE_SRC_SD_CARD_H
#pragma once

#include "sdlib\SdFat.h"
#include <SPI.h>
#include "string_pair.h"

namespace device_lib {

class SdCard
{
    public:
        SdCard();

        void append_record(const String, const String);
        void read_last_record();
        void next_record();
        void prev_record();
        void delete_file();
        String get_record_date() { return _record._date;};
        String get_record_barcode() { return _record._barcode;};

        void delete_record(int);     //TODO
        void read_file();    //DEBUG
        void read_file_reverse();

    private:
        SdFat _sd;
        const char _path[9];
        StringPair _record;
        int _cursor = 0;
        int parse_header(SdFile&);
        void write_header(SdFile&, const int);
        static const byte _headerSize = 8;  //bytes reserved at top of file, stores current # records
                                            //a further two bytes are also reserved for \r and \n

};
}
#endif //DEVICE_SRC_SD_CARD_H


/*type function()                                                                                  */
//
//
