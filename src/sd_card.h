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

namespace device_lib {

class SdCard
{
    public:
        SdCard();

        void appendEntry(String, String);
        void createDummy();
        void deleteEntry(int);
        void readFile();
        void deleteFile();
        void readBack();

    private:
        SdFat _sd;
        const char _path[9];
        int fetchNumEntries(SdFile&);
        void writeNumEntries(SdFile&, int);
        static const byte headerSize = 8;  //bytes reserved at top of file, stores current # entries

};
}
#endif //DEVICE_SRC_SD_CARD_H


/*type function()                                                                                  */
//
//
