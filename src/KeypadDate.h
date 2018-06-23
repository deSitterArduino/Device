/*
  KeypadDate.h - Wrapper of M. Stanley amd A. Brevig's Keypad Libiary v3.1
  Changed callback eventListener function's arguments to include a pointer to 
  the instance of this class to which the instance of the Keypad object calling eventListener belongs.
  This is for the purpose of referencing non-static members directly from the static callback function.
  
  Used to read key-presses from a 3x4 matrix keypad
  and produce valid dates from the input.
  Created by Greg Boucher, June 2018
*/

#ifndef KEYPADDATE_H
#define KEYPADDATE_H
#pragma once

#include "Keypad.h"

namespace Device_lib {
class Device;           //forward declaration of the parent class

    class KeypadDate
    {
        public:
            KeypadDate(Device*);
            
            Keypad keypad;
            static void keypadEvent(char, KeypadDate*);   //callback function called by keypad.
                                                          //Passes a pointer to the instance of this KeypadDate
                                                          //class to which the calling keypad object belongs.
            
            char listenForKey();
            Device* p_parent;

            String lockCode = "";
            String const correctLockCode = "3663";
            void addToLockCode(char);

            String date = "";
            void addToDate(char);
            bool isValid();

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
            
        private:
            static const byte ROWS = 4;
            static const byte COLS = 3;
            char keys[ROWS][COLS] = {
                {'1','2','3'},
                {'4','5','6'},
                {'7','8','9'},
                {'*','0','#'}
            };
            byte rowPins[ROWS] = {5, 4, 3, 2};
            byte colPins[COLS] = {8, 7, 6};
    };
}
#endif //KEYPADDATE_H
