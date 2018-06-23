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
              Serial.println(barcodeReader.getSlaveSize());
                barcodeReader.readSlaveBuffer();
                return barcodeReader.getBarcode();
            }
        }
        return "";
    }
    
    void Device::updateDeviceState(DeviceState newState) {
        deviceState = newState;
        Serial.print(deviceState);
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
