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
    clear_slave_buffer();
    pinMode(_scanPin, OUTPUT);
}

void BarcodeReader::clear_slave_buffer() {    //clear the slave buffer by reading all available bytes
    int sizeCheck = read_slave_size();
    if (sizeCheck > 0) {
        read_slave_buffer();
        clear_host_buffer();
    }
}

int BarcodeReader::read_slave_size() {
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

void BarcodeReader::read_slave_buffer() {
    char c = ' ';
    clear_host_buffer();
    Wire.beginTransmission(_slaveAddress);
    Wire.write(_bufferRegister);
    Wire.endTransmission();
    Wire.requestFrom(_slaveAddress, _slaveSize);
    while (Wire.available())    //only reads max 32bytes at a time
    {
        --_slaveSize;
        c = char(Wire.read());
        if (!((c == '\r') | (c == '\n'))) _hostBuffer += c; //ignore tail \r and \n
    }
    if (_slaveSize > 0) read_slave_buffer();    //keep calling this function until all bytes are read
}

bool BarcodeReader::scan() {
    if (digitalRead(_scanPin) == LOW) digitalWrite(_scanPin, HIGH);
    int sizeCheck = read_slave_size();
    if (sizeCheck > 0) {
        stop_scan();
        Serial.print(F("(DEBUG) FIRST PASS SIZE: "));
        Serial.println(sizeCheck);
        delay(200);    //required to give the buffer on the host controler time to fill
        sizeCheck = read_slave_size();
        Serial.print(F("(DEBUG) SECOND PASS SIZE: "));
        Serial.println(sizeCheck);
        read_slave_buffer();
        return true;
    }
    return false;
}

void BarcodeReader::stop_scan() {
    digitalWrite(_scanPin, LOW);
}

bool BarcodeReader::is_valid() {
    //TODO
}









}
