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
        while (deviceState = e_SCAN) {
            char key = keypadDate.listenForKey();
            if (deviceState != e_SCAN) break;
            Device_lib::BarcodeReader barcodeReader;
            if (barcodeReader.readSlaveSize() > 0) {
                Serial.print("SLAVE SIZE: ");
                Serial.println(barcodeReader.getSlaveSize());
                Serial.print("INDEX SIZE: ");
                Serial.println(barcodeReader.index);
                barcodeReader.readSlaveBuffer();
                return barcodeReader.getBarcode();
            }
        }
        return "";
    }

    void Device::updateDeviceState(DeviceState newState) {
        deviceState = newState;
        Serial.print("DEVICE STATE: ");
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
               String barcode = beginScan();
               if (barcode != "") {
                  Serial.println(barcode);
               } else {
                  Serial.println("No Code ");
               }
               break;
            }
        }
    }
}
