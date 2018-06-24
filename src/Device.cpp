/*

  Created by Greg Boucher, June 2018
*/

#include "Device.h"
#include "BarcodeReader.h"

namespace Device_lib {

    Device::Device()
        :keypadDate(this)
    {
    }

    void Device::updateDeviceState(DeviceState newState) {      //changes deviceState and resets appropriate members
        deviceState = newState;
        Serial.print("(DEBUG) DEVICE STATE: ");
        Serial.println(deviceState);
        switch (deviceState) {
            case e_LOCK: {
                keypadDate.clearInputCode();
                break;
            }
            case e_DATE: {
                keypadDate.clearInputDate();
                break;
            }
            case e_LIST: {

                break;
            }
            case e_SCAN: {                                      //set when holding the scan key after inputting a valid date
               String barcode = beginScan();                    //(loop)returns only with barcode or if scan key is released (returns "")
               if (barcode != "") {
                  Serial.println(barcode);
                  updateDeviceState(e_DATE);
               } else {
                  Serial.println("(DEBUG) NO CODE ");
               }
               break;
            }
        }
    }

    String Device::beginScan() {
        Device_lib::BarcodeReader barcodeReader;
        while (true) {
            keypadDate.listenForKey();                          //will trigger callback event if keyState has changed
            if (deviceState != e_SCAN) {                        //releasing hold of the key initiating the scan will reset the deviceState to e_INPUT
                barcodeReader.stopScan();                       //hence we turn OFF the Barcode Reader and exit the loop
                break;
            }
            if (barcodeReader.Scan()) {                         //turns ON the Barcode Reader and returns true if a barcode was read
                return barcodeReader.getBarcode();
            }
        }
        return "";
    }

    DeviceState Device::getState() {
        return deviceState;
    }
}
