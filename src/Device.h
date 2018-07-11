/*

  Created by Greg Boucher, June 2018
*/

#ifndef DEVICE_SRC_DEVICE_H
#define DEVICE_SRC_DEVICE_H
#pragma once

#include "keypad_date.h"
#include "enum_device_state.h"

namespace device_lib {

class Device
{
    public:
        Device();

        KeypadDate keypadDate;            //handles all keypad events
        State const getState();           //returns current DeviceState
        void updateDeviceState(State);    //changes deviceState and resets appropriate members

    private:
        State deviceState_ = State::DATE;  //start at LOCK
        String beginScan();    //performs scan, exit if the scan key is released, or barcode scanned

};
}
#endif //DEVICE_SRC_DEVICE_H
