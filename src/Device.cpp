//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "device.h"
#include "barcode_reader.h"

namespace device_lib {

Device::Device()
    :_keypadDate(this)
{
}

char Device::listenForKey() {
    return _keypadDate.listenForKey();
}

void Device::updateDeviceState(State state) {    //changes deviceState and resets members
    _state = state;
    Serial.print("(DEBUG) DEVICE STATE: ");
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
                updateDeviceState(DATE);
            } else {
                Serial.println("(DEBUG) NO CODE ");
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
        if (barcodeReader.Scan()) {     //turns ON the Barcode Reader, true if a barcode was read
            return barcodeReader.getBarcode();
        }
    }
    return "";
}
}
