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

        char listenForKey();   //calls keypad.getKey() in loop, so that callback event can be thrown
        void clearInputCode() {_inputCode = "";};
        void clearInputDate() {_inputDate = "";};

    private:
        void addToDate(char);
        void addToLockCode(char);
        bool isValid();

        Device* _parent;
        String _inputCode = "";
        String const _correctCode = "3663";    //food
        String _inputDate = "";
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

        static void keypadEvent(char, KeypadDate*);
        void keyOne(KeyState);
        void keyTwo(KeyState);
        void keyThree(KeyState);
        void keyFour(KeyState);
        void keyFive(KeyState);
        void keySix(KeyState);
        void keySeven(KeyState);
        void keyEight(KeyState);
        void keyNine(KeyState);
        void keyZero(KeyState);
        void keyStar(KeyState);
        void keyHash(KeyState);
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
