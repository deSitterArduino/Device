/*
  BarcodeReader.h - Library for reading barcodes from a
  HobbyTronics USB host controller via an I2C bus.
  Created by Greg Boucher, June 2018
*/

#ifndef DEVICE_SRC_BARCODEREADER_H
#define DEVICE_SRC_BARCODEREADER_H
#pragma once

#include <Wire.h>
#include "Arduino.h"

namespace device_lib {

class BarcodeReader
{
    public:
        BarcodeReader();            //the slave buffer is cleared upon construction
        String const getBarcode();  //return the current contents of hostBuffer
        byte const getSlaveSize();  //returns the contents of slaveSize
        bool Scan();                //(I2C)turns ON Barcode Scanner, true if barcode read
        void stopScan();            //turns OFF the Barcode Scanner
                                    //TODO reduce to one function toggleScan()

    private:
        void clearHostBuffer();     //set the local buffer to empty string
        void clearSlaveBuffer();    //(I2C) reads chars from slave into hostBuffer, then clears
        bool isValid();             //TODO: Is there an easy way to check if a barcode is valid?
        int readSlaveSize();        //(I2C)return the size of the slave buffer
        void readSlaveBuffer();     //(I2C)read the contents of the slave buffer into hostBuffer
        String hostBuffer_;          //The slave uses a 256 byte buffer
        byte slaveSize_;             //size(bytes) of the slaves current buffer
        byte scanPin_ = 9;           //pin to transistor which switches ON/OFF the Barcode Reader
        static const byte slaveAddress_ = 41;
        static const byte bufferRegister_ = 0;   //internal register of the slave's buffer
        static const byte sizeRegister_ = 1;     //internal register of the slave's buffer size
};
}
#endif //DEVICE_SRC_BARCODEREADER_H
