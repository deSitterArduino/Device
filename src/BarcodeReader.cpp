/*
  BarcodeReader.cpp - Library for reading barcodes from a
  HobbyTronics USB host controller via an I2C bus.
  Created by Greg Boucher, June 2018
*/

#include "BarcodeReader.h"

namespace Device_lib {

    BarcodeReader::BarcodeReader()
        :hostBuffer{""},
        slaveSize{0}
    {
          //clearSlaveBuffer();
    }

    int BarcodeReader::getSlaveSize() {
        return slaveSize;
    }

    int BarcodeReader::readSlaveSize() {
         Wire.begin();
         Wire.beginTransmission(slaveAddress);
         Wire.write(slaveSizeAddress);
         Wire.endTransmission();
         Wire.requestFrom(slaveAddress, 1);
         while (Wire.available())
         {
                 slaveSize = Wire.read();
                 index = slaveSize;
         }
         if (slaveSize > 0) {
             return slaveSize;
         } else {
             index = 0;
             return slaveSize = 0;
         }
         //return (slaveSize > 0) ? slaveSize : slaveSize = 0;
    }

    void BarcodeReader::readSlaveBuffer() {
        //clearHostBuffer();
        Wire.beginTransmission(slaveAddress);
        Wire.write(slaveBufferAddress);
        Wire.endTransmission();
        while (index > 0) {
            Wire.requestFrom(slaveAddress, index, true);
            while (Wire.available())
            {
                hostBuffer += char(Wire.read());
                --index;
            }
        }
    }

    void BarcodeReader::clearHostBuffer() {
        hostBuffer = "";
    }

    void BarcodeReader::clearSlaveBuffer() {      //clear the slave buffer by reading all available bytes
        if (readSlaveSize() > 0) {
            readSlaveBuffer();
            clearHostBuffer();
        }
    }

    bool BarcodeReader::isValid() {
        return true;
    }

    String BarcodeReader::getBarcode() {
        return hostBuffer;
    }









}
