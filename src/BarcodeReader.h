/*
  BarcodeReader.h - Library for reading barcodes from a
  HobbyTronics USB host controller via an I2C bus.
  Created by Greg Boucher, June 2018
*/

#ifndef BARCODEREADER_H
#define BARCODEREADER_H
#pragma once

#include <Wire.h>
#include "Arduino.h"

namespace Device_lib {

    class BarcodeReader
    {
        public:
            BarcodeReader();                            //the slave buffer is cleared upon construction
            String getBarcode();                        //return the current contents of hostBuffer
            byte getSlaveSize();                        //returns the contents of slaveSize
            bool Scan();                                //(I2C)turns ON the Barcode Scanner and returns true if a barcode was read into hostBuffer
            void stopScan();                            //turns OFF the Barcode Scanner

        private:
            void clearHostBuffer();                     //set the local buffer to empty string
            void clearSlaveBuffer();                    //(I2C) clears the buffer on the slave by reading into hostBuffer then clearing it
            bool isValid();                             //TODO: Is there an easy way to check if a barcode is valid?
            int readSlaveSize();                        //(I2C)return the size of the slave buffer
            void readSlaveBuffer();                     //(I2C)read the contents of the slave buffer into hostBuffer

            String hostBuffer;                          //The slave uses a 256 byte buffer
            byte slaveSize;                             //size(bytes) of the slaves current buffer
            byte scanPin = 9;                           //pin to the base of the transistor which switches ON/OFF the Barcode Reader
            static const byte slaveAddress = 41;        //address of the slave device (default 0x29 = dec[41])
            static const byte BufferRegister = 0;       //internal register of the slave's buffer
            static const byte SizeRegister = 1;         //internal register of the slave's buffer size value
    };
}
#endif //BARCODEREADER_H
