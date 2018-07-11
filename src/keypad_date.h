/*
  KeypadDate.h - Wrapper of M. Stanley amd A. Brevig's Keypad Libiary v3.1
  Changed callback eventListener function's arguments to include a pointer to the instance of this
  class to which the instance of the Keypad object calling eventListener belongs. This is for the
  purpose of referencing non-static members directly from the static callback function.

  Used to read key-presses from a 3x4 matrix keypad
  and produce valid dates from the input.
  Created by Greg Boucher, June 2018
*/

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

        char listenForKey();    //call keypad.getKey() in loop, so that callback event can be thrown
        void clearInputCode();
        void clearInputDate();

    private:
        void addToDate(char);
        void addToLockCode(char);
        bool isValid();

        Device* parent_;
        String inputCode_ = "";
        String const correctCode_ = "3663";    //food
        String inputDate_ = "";
        static const byte ROWS_s = 4;
        static const byte COLS_s = 3;
        char keys[ROWS_s][COLS_s] = {
            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'},
            {'*','0','#'}
        };
        byte rowPins[ROWS_s] = {5, 4, 3, 2};
        byte colPins[COLS_s] = {8, 7, 6};

        Keypad keypad;
        //callback function called by keypad. Passes a pointer to the instance of this KeypadDate
        //class to which the calling keypad object belongs.
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
