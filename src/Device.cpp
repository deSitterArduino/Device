//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "device.h"
#include "barcode_reader.h"
#include "sd_card.h"

namespace device_lib {

Device::Device()
    :_keypadDate(this)
{
}

void Device::temp() {
    SdCard sdCard;
    //sdCard.readBack();
    //sdCard.readFile();
    //sdCard.deleteFile();
    //sdCard.readFile();
}

char Device::listenForKey() {
    return _keypadDate.listenForKey();
}

void Device::updateDeviceState(State state) {    //changes deviceState and resets members
    _state = state;
    Serial.print(F("(DEBUG) DEVICE STATE: "));
    Serial.println(_state);
    switch (_state) {
        case LOCK: {
            _keypadDate.clearInputCode();
            break;
        }
        case DATE: {
            _keypadDate.clearInputDate();
            break;
        }
        case LIST: {

            break;
        }
        case SCAN: {    //set when holding the scan key after inputting a valid date
            String barcode = beginScan();   //(loop)returns only with barcode or scan key released
            if (barcode != "") {
                Serial.println(barcode);
                SdCard sdCard;
                sdCard.appendEntry(_keypadDate.getDate(), barcode);
                sdCard.readFile(); //DEBUG
                updateDeviceState(DATE);
            } else {
                Serial.println(F("(DEBUG) NO CODE "));
            }
            break;
        }
    }
}

String Device::beginScan() {
    BarcodeReader barcodeReader;
    while (true) {
        _keypadDate.listenForKey();      //will trigger callback event if keyState has changed
        if (_state != SCAN) {     //releasing hold of scan key will reset the State to INPUT
            barcodeReader.stopScan();   //hence we turn OFF the Barcode Reader and exit the loop
            break;
        }
        if (barcodeReader.scan()) {     //turns ON the Barcode Reader, true if a barcode was read
            return barcodeReader.getBarcode();
        }
    }
    return "";
}
}
