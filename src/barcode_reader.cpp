//**************************************************************************************************
//    BarcodeReader.cpp - Library for reading barcodes from a
//    HobbyTronics USB host controller via an I2C bus.
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "barcode_reader.h"

namespace device_lib {

BarcodeReader::BarcodeReader()
    :_hostBuffer{""},
    _slaveSize{0}
{
    clearSlaveBuffer();
    pinMode(_scanPin, OUTPUT);
}

void BarcodeReader::clearSlaveBuffer() {    //clear the slave buffer by reading all available bytes
    int sizeCheck = readSlaveSize();
    if (sizeCheck > 0) {
        readSlaveBuffer();
        clearHostBuffer();
    }
}

int BarcodeReader::readSlaveSize() {
    Wire.begin();
    Wire.beginTransmission(_slaveAddress);
    Wire.write(_sizeRegister);
    Wire.endTransmission();
    Wire.requestFrom(_slaveAddress, 1);
    while (Wire.available())
    {
        _slaveSize = Wire.read();
    }
    return (_slaveSize > 0) ? _slaveSize : _slaveSize = 0;
}

void BarcodeReader::readSlaveBuffer() {
    clearHostBuffer();
    Wire.beginTransmission(_slaveAddress);
    Wire.write(_bufferRegister);
    Wire.endTransmission();
    Wire.requestFrom(_slaveAddress, _slaveSize);
    while (Wire.available())    //only reads max 32bytes at a time
    {
        --_slaveSize;
        _hostBuffer += char(Wire.read());
    }
    if (_slaveSize > 0) readSlaveBuffer();    //keep calling this function until all bytes are read
}

bool BarcodeReader::Scan() {
    if (digitalRead(_scanPin) == LOW) digitalWrite(_scanPin, HIGH);
    int sizeCheck = readSlaveSize();
    if (sizeCheck > 0) {
        stopScan();
        Serial.print("(DEBUG) FIRST PASS SIZE: ");
        Serial.println(sizeCheck);
        delay(200);    //required to give the buffer on the host controler time to fill
        sizeCheck = readSlaveSize();
        Serial.print("(DEBUG) SECOND PASS SIZE: ");
        Serial.println(sizeCheck);
        readSlaveBuffer();
        return true;
    }
    return false;
}

void BarcodeReader::stopScan() {
    digitalWrite(_scanPin, LOW);
}

bool BarcodeReader::isValid() {
    //TODO
}









}
