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
            DeviceState deviceState = e_LOCK;
            KeypadDate keypadDate;
            void updateDeviceState(DeviceState);
            String beginScan();

        private:
            
    };
}
#endif //DEVICE_H
