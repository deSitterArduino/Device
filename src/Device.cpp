/*

  Created by Greg Boucher, June 2018
*/

#include "device.h"
#include "barcode_reader.h"

namespace device_lib {

Device::Device()
    :keypadDate(this)
{
}

void Device::updateDeviceState(State state) {    //changes deviceState and resets members
    deviceState_ = state;
    Serial.print("(DEBUG) DEVICE STATE: ");
    Serial.println(deviceState_);
    switch (deviceState_) {
        case LOCK: {
            keypadDate.clearInputCode();
            break;
        }
        case DATE: {
            keypadDate.clearInputDate();
            break;
        }
        case LIST: {

            break;
        }
        case SCAN: {    //set when holding the scan key after inputting a valid date
            String barcode = beginScan();   //(loop)returns only with barcode or key released
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
    device_lib::BarcodeReader barcodeReader;
    while (true) {
        keypadDate.listenForKey();      //will trigger callback event if keyState has changed
        if (deviceState_ != SCAN) {     //releasing hold of scan keywill reset the State to INPUT
            barcodeReader.stopScan();   //hence we turn OFF the Barcode Reader and exit the loop
            break;
        }
        if (barcodeReader.Scan()) {     //turns ON the Barcode Reader, true if a barcode was read
            return barcodeReader.getBarcode();
        }
    }
    return "";
}

State const Device::getState() {
    return deviceState_;
}
}
