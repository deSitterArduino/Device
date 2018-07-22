//**************************************************************************************************
//    BarcodeReader.h - Library for reading barcodes from a
//    HobbyTronics USB host controller via an I2C bus.
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

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
        String const get_barcode() {return _hostBuffer;};
        byte const get_slave_size() {return _slaveSize;};
        bool scan();                //(I2C)turns ON Barcode Scanner, true if barcode read
        void stop_scan();            //turns OFF the Barcode Scanner
                                    //TODO reduce into one function toggleScan()

    private:
        void clear_host_buffer() {_hostBuffer = "";};
        void clear_slave_buffer();    //(I2C) reads chars from slave into hostBuffer, then clears
        bool is_valid();             //TODO: Is there an easy way to check if a barcode is valid?
        int read_slave_size();        //(I2C)return the size of the slave buffer
        void read_slave_buffer();     //(I2C)read the contents of the slave buffer into hostBuffer
        String _hostBuffer;          //The slave uses a 256 byte buffer
        byte _slaveSize;             //size(bytes) of the slaves current buffer
        byte _scanPin = 9;           //pin to transistor which switches ON/OFF the Barcode Reader
        static const byte _slaveAddress = 41;
        static const byte _bufferRegister = 0;   //internal register of the slave's buffer
        static const byte _sizeRegister = 1;     //internal register of the slave's buffer size
};
}
#endif //DEVICE_SRC_BARCODEREADER_H


/*byte Scan()                                                                                     */
//@BRIEF (I2C) Turns ON Barcode Scanner
//@RETURN True if barcode is read into _hostBuffer

/*void clearSlaveBuffer()                                                                         */
//@BRIEF (I2C) Clears the buffer on the slave by reading all available bytes into hostBuffer,
//then sets the hostBuffer back to empty string

/*int readSlaveSize()                                                                             */
//@BRIEF (I2C) fetches the number of characters currently in the slave's buffer
//@RETURN the size of the slave buffer in bytes

/*void readSlaveBuffer()                                                                          */
//@BRIEF (I2C) Reads the current contents of the slave buffer into hostBuffer
