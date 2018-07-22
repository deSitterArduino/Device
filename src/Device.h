//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

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

        char listen_for_key();              //calls keypadDate's listenForKey(). Call in loop()
        State const get_state() {return _state;};
        void update_device_state(State);    //changes deviceState and resets appropriate members
        void temp();    //DEBUG

    private:
        KeypadDate _keypadDate;            //handles all keypad events
        State _state = State::DATE; //start at LOCK
        String begin_scan();    //performs scan, exit if the scan key is released, or barcode scanned

};
}
#endif //DEVICE_SRC_DEVICE_H


/*char listenForKey()                                                                              */
//@BRIEF Calls keypadDate's listenForKey(). Call in loop()
//@RETURN the key being pressed, else an empty char ""

/*void updateDeviceState(State)                                                                    */
//@BRIEF Changes the current deviceState
//@PARAM The new State to change too

/*String beginScan()                                                                               */
//@BRIEF Creates barcodeReader object, sets scanPin high. Function will loop until either the
//scan key released, or a barcode is read into barcodeReader::_hostBuffer
//@RETURN the barcode read, else an empty string
