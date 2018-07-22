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

char Device::listen_for_key() {
    return _keypadDate.listen_for_key();
}

void Device::update_device_state(State state) {    //changes deviceState and resets members
    _state = state;
    Serial.print(F("(DEBUG) DEVICE STATE: "));
    Serial.println(_state);
    switch (_state) {
        case LOCK: {
            _keypadDate.clear_input_code();
            break;
        }
        case DATE: {
            _keypadDate.clear_input_date();
            break;
        }
        case LIST: {

            break;
        }
        case SCAN: {    //set when holding the scan key after inputting a valid date
            String barcode = begin_scan();   //(loop)returns only with barcode or scan key released
            if (barcode != "") {
                Serial.println(barcode);
                SdCard sdCard;
                sdCard.append_record(_keypadDate.get_date(), barcode);
                sdCard.read_file(); //DEBUG
                update_device_state(DATE);
            } else {
                Serial.println(F("(DEBUG) NO CODE "));
            }
            break;
        }
    }
}

String Device::begin_scan() {
    BarcodeReader barcodeReader;
    while (true) {
        _keypadDate.listen_for_key();      //will trigger callback event if keyState has changed
        if (_state != SCAN) {     //releasing hold of scan key will reset the State to INPUT
            barcodeReader.stop_scan();   //hence we turn OFF the Barcode Reader and exit the loop
            break;
        }
        if (barcodeReader.scan()) {     //turns ON the Barcode Reader, true if a barcode was read
            return barcodeReader.get_barcode();
        }
    }
    return "";
}
}
