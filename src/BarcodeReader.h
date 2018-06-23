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
            BarcodeReader();                        //!the slave buffer is cleared upon construction! (TODO Change this so we pull from the buffer 32bytes at a time and arrive at the last scanned code)

            int readSlaveSize();                    //return the size of the slave buffer
            void readSlaveBuffer();                 //read the contents of the slave buffer into hostBuffer
            String getBarcode();                    //return the current contents of hostBuffer
            int getSlaveSize();
            int index; 

        private:
            void clearHostBuffer();                 //set the local buffer to '\0' null-terminated
            void clearSlaveBuffer();                //clear the buffer on the slave (read I2C to clear)
            bool isValid();

            String hostBuffer;                      //(The slave uses a 256 byte buffer)
            int slaveSize;                          //size(bytes) of the slaves current buffer
            static const int slaveAddress = 41;            //I2C slave device address (default 0x29 = dec[41])
            static const int slaveBufferAddress = 0;       //internal register of the slave's buffer
            static const int slaveSizeAddress = 1;         //internal register of the slave's buffer size value
    };
}
#endif //BARCODEREADER_H
