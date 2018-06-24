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

    String Device::beginScan() {
        Device_lib::BarcodeReader barcodeReader;
        while (true) {
            keypadDate.listenForKey();
            if (deviceState != e_SCAN) {
                barcodeReader.stopScan();
                break;
            }
            if (barcodeReader.Scan()) {         //turns ON the laser and returns true if a barcode was read
                return barcodeReader.getBarcode();
            }
        }
        return "";
    }

    void Device::updateDeviceState(DeviceState newState) {
        deviceState = newState;
        Serial.print("(DEBUG) DEVICE STATE: ");
        Serial.println(deviceState);
        switch (deviceState) {
            case e_LOCK: {
                keypadDate.lockCode = "";
                break;
            }
            case e_DATE: {
                keypadDate.date = "";
                break;
            }
            case e_LIST: {

                break;
            }
            case e_SCAN: {
               String barcode = beginScan();     //exits only with barcode or if scan key is released (returns "")
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
}
