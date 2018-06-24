/*

  Created by Greg Boucher, June 2018
*/

#ifndef DEVICE_H
#define DEVICE_H
#pragma once

#include "KeypadDate.h"
#include "e_DeviceState.h"

namespace Device_lib {

    class Device
    {
        public:
            Device();

            KeypadDate keypadDate;                  //handles all keypad events
            DeviceState getState();                 //returns current DeviceState
            void updateDeviceState(DeviceState);    //changes deviceState and resets appropriate members


        private:
            DeviceState deviceState = e_DATE;       //start at e_LOCK
            String beginScan();                     //performs a barcode scan, exiting only if the scan key is released, or a barcode is scanned

    };
}
#endif //DEVICE_H
