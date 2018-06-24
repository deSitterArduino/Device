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
          clearSlaveBuffer();
          pinMode(scanPin, OUTPUT);
    }

    void BarcodeReader::stopScan() {
        digitalWrite(scanPin, LOW);
    }

    bool BarcodeReader::Scan() {
        if (digitalRead(scanPin) == LOW) digitalWrite(scanPin, HIGH);
        int sizeCheck = readSlaveSize();
        if (sizeCheck > 0) {
            stopScan();
            Serial.print("(DEBUG) FIRST PASS SIZE: ");
            Serial.println(sizeCheck);
            delay(200);   //required to give the buffer on the host controler time to fill
            sizeCheck = readSlaveSize();
            Serial.print("(DEBUG) SECOND PASS SIZE: ");
            Serial.println(sizeCheck);
            readSlaveBuffer();
            return true;
        }
        return false;
    }

    int BarcodeReader::getSlaveSize() {
        return slaveSize;
    }

    int BarcodeReader::readSlaveSize() {
         Wire.begin();
         Wire.beginTransmission(slaveAddress);
         Wire.write(SizeRegister);
         Wire.endTransmission();
         Wire.requestFrom(slaveAddress, 1);
         while (Wire.available())
         {
                 slaveSize = Wire.read();
         }
         return (slaveSize > 0) ? slaveSize : slaveSize = 0;
    }

    void BarcodeReader::readSlaveBuffer() {
        clearHostBuffer();
        Wire.beginTransmission(slaveAddress);
        Wire.write(BufferRegister);
        Wire.endTransmission();
        Wire.requestFrom(slaveAddress, slaveSize);
        while (Wire.available())
        {
            --slaveSize;
            hostBuffer += char(Wire.read());
        }
        if (slaveSize > 0) readSlaveBuffer();
    }

    void BarcodeReader::clearHostBuffer() {
        hostBuffer = "";
    }

    void BarcodeReader::clearSlaveBuffer() {      //clear the slave buffer by reading all available bytes
        int ss = readSlaveSize();
        if (ss > 0) {
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
