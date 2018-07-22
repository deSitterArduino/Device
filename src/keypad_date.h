//**************************************************************************************************
//    KeypadDate.h - Wrapper of M. Stanley amd A. Brevig's Keypad Libiary v3.1
//    Changed callback eventListener function's arguments to include a pointer to
//    the instance of this class to which the instance of the Keypad object calling eventListener
//    belongs. This is for the purpose of referencing non-static members directly from the static
//    callback function.
//
//    Used to read key-presses from a 3x4 matrix keypad and produce valid dates from the input.
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#ifndef DEVICE_SRC_KEYPADDATE_H
#define DEVICE_SRC_KEYPADDATE_H
#pragma once

#include "keypad.h"

namespace device_lib {
class Device;    //forward declaration of the parent class

class KeypadDate
{
    public:
        KeypadDate(Device*);

        char listen_for_key();  //calls keypad.getKey() in loop, so that callback event can be thrown
        void clear_input_code() {_code = "";};
        void clear_input_date() {_date = "";};
        String get_date() {return _date;};

    private:
        void append_date(char);
        void append_lockcode(char);
        bool is_valid();

        Device* _parent;
        String _code = "";
        String const _correctCode = "3663";    //food
        String _date = "";
        static const byte _ROWS = 4;
        static const byte _COLS = 3;
        char keys[_ROWS][_COLS] = {
            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'},
            {'*','0','#'}
        };
        byte _rowPins[_ROWS] = {5, 4, 3, 2};
        byte _colPins[_COLS] = {8, 7, 6};

        Keypad _keypad;

        static void keypad_event(char, KeypadDate*);
        void key_one(KeyState);
        void key_two(KeyState);
        void key_three(KeyState);
        void key_four(KeyState);
        void key_five(KeyState);
        void key_six(KeyState);
        void key_seven(KeyState);
        void key_eight(KeyState);
        void key_nine(KeyState);
        void key_zero(KeyState);
        void key_star(KeyState);
        void key_hash(KeyState);
};
}
#endif //DEVICE_SRC_KEYPADDATE_H


/*char listenForKey()                                                                             */
//@BRIEF Calls _keypad.getKey(), which uses the callback function keypadEvent to parse keypad input

/*void addToDate(char)                                                                            */
//@BRIEF Adds a key character to the inputDate_ string, so long as .length() < 6
//@PARAM the charracter to be added

/*void addToLockCode(char)                                                                        */
//@BRIEF Adds a key character to the _inputCode string, so long as .length() < 4
//@PARAM the charracter to be added

/*bool isValid()                                                                                  */
//@BRIEF TODO
//@RETURN True if the inputted date is a valid date

/*static void keypadEvent(char, keypadDate*)                                                      */
//@BRIEF Callback function called by _keypad
//@PARAM The key that triggered this event
//@PARAM The pointer to the instance of this KeypadDate class to which the calling keypad_ object
//belongs.

/*void keyOne(KeyState) ----> keyHash(KeyState)                                                   */
//@BRIEF Called in keypadEvent callback function. Performs key specific functionalty based of the
//devices current state.
//@PARAM The state of the key which triggered the callback event (e.g PRESSED, HOLD, RELEASED)
