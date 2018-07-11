/*
BarcodeReader.cpp - Library for reading barcodes from a
HobbyTronics USB host controller via an I2C bus.
Created by Greg Boucher, June 2018
*/

#include "barcode_reader.h"

namespace device_lib {

BarcodeReader::BarcodeReader()
    :hostBuffer_{""},
    slaveSize_{0}
{
    clearSlaveBuffer();
    pinMode(scanPin_, OUTPUT);
}

void BarcodeReader::clearHostBuffer() {
    hostBuffer_ = "";
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
    Wire.beginTransmission(slaveAddress_);
    Wire.write(sizeRegister_);
    Wire.endTransmission();
    Wire.requestFrom(slaveAddress_, 1);
    while (Wire.available())
    {
        slaveSize_ = Wire.read();
    }
    return (slaveSize_ > 0) ? slaveSize_ : slaveSize_ = 0;
}

void BarcodeReader::readSlaveBuffer() {
    clearHostBuffer();
    Wire.beginTransmission(slaveAddress_);
    Wire.write(bufferRegister_);
    Wire.endTransmission();
    Wire.requestFrom(slaveAddress_, slaveSize_);
    while (Wire.available())    //only reads max 32bytes at a time
    {
        --slaveSize_;
        hostBuffer_ += char(Wire.read());
    }
    if (slaveSize_ > 0) readSlaveBuffer();    //keep calling this function until all bytes are read
}

bool BarcodeReader::Scan() {
    if (digitalRead(scanPin_) == LOW) digitalWrite(scanPin_, HIGH);
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
    digitalWrite(scanPin_, LOW);
}

byte const BarcodeReader::getSlaveSize() {
    return slaveSize_;
}

String const BarcodeReader::getBarcode() {
    return hostBuffer_;
}

bool BarcodeReader::isValid() {
    //TODO
}









}
