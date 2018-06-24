/*
  KeypadDate.cpp - Wrapper of M. Stanley amd A. Brevig's Keypad Libiary v3.1
  Changed callback eventListener function's arguments to include a pointer to
  the instance of this class to which the instance of the Keypad object calling eventListener belongs.
  This is for the purpose of referencing non-static members directly from the static callback function.

  Used to read key-presses from a 3x4 matrix keypad
  and produce valid dates from the input.
  Created by Greg Boucher, June 2018
*/

#include "KeypadDate.h"
#include "Device.h"  //definition required for access to parent 'Device class' through parent pointer 'p_parent'

namespace Device_lib {

    KeypadDate::KeypadDate(Device* tp_parent)
    :p_parent(tp_parent), keypad{Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, this)}
    {
        keypad.addEventListener(keypadEvent); //provide function pointer to be called when a
                                              //change of keystate occurs.

    }

    char KeypadDate::listenForKey() {
        return keypad.getKey();
    }

    static void KeypadDate::keypadEvent(char key, KeypadDate* p_KeypadDate) {
        KeyState keyState = p_KeypadDate->keypad.getState();
        if (keyState != IDLE) {
            switch (key) {
                case '1': p_KeypadDate->keyOne(keyState);break;
                case '2': p_KeypadDate->keyTwo(keyState);break;
                case '3': p_KeypadDate->keyThree(keyState);break;
                case '4': p_KeypadDate->keyFour(keyState);break;
                case '5': p_KeypadDate->keyFive(keyState);break;
                case '6': p_KeypadDate->keySix(keyState);break;
                case '7': p_KeypadDate->keySeven(keyState);break;
                case '8': p_KeypadDate->keyEight(keyState);break;
                case '9': p_KeypadDate->keyNine(keyState);break;
                case '0': p_KeypadDate->keyZero(keyState);break;
                case '*': p_KeypadDate->keyStar(keyState);break;
                case '#': p_KeypadDate->keyHash(keyState);break;
            }
        }
    }

    void KeypadDate::addToLockCode(char key) {
        if (lockCode.length() < 4) {
            lockCode = lockCode + key;
        }
    }

    void KeypadDate::addToDate(char key) {
        if (date.length() < 6) {
            date = date + key;
        }
    }

    bool KeypadDate::isValid() {
        return true;
    }

    void KeypadDate::keyOne(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('1');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('1');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyTwo(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('2');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('2');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyThree(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('3');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('3');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyFour(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('4');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('4');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyFive(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('5');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('5');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keySix(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('6');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('6');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keySeven(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('7');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('7');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyEight(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('8');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('8');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyNine(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('9');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('9');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyZero(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        addToLockCode('0');
                        Serial.println(lockCode);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                 switch (keyState) {
                    case PRESSED: {
                        addToDate('0');
                        Serial.println(date);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyStar(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        p_parent->updateDeviceState(e_LOCK);
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                switch (keyState) {
                    case PRESSED: {
                        p_parent->updateDeviceState(e_DATE);
                        break;
                    }
                    case HOLD: {
                        p_parent->updateDeviceState(e_LIST);
                        break;
                    }
                }
                break;
            }
        }
    }

    void KeypadDate::keyHash(KeyState keyState) {
        switch (p_parent->deviceState) {
            case e_LOCK: {
                switch (keyState) {
                    case PRESSED: {
                        if (lockCode.equals(correctLockCode)) {
                            Serial.println("CORRECT CODE ");
                            p_parent->updateDeviceState(e_DATE);
                        } else {
                            Serial.println("INVALID CODE ");
                            p_parent->updateDeviceState(e_LOCK);
                        }
                        break;
                    }
                }
                break;
            }
            case e_DATE: {
                switch (keyState) {
                    case HOLD: {
                        if (isValid()) {
                            Serial.println("(DEBUG) VALID DATE ");
                            p_parent->updateDeviceState(e_SCAN);
                        }
                        break;
                    }
                }
                break;
            }
            case e_SCAN: {
                switch (keyState) {
                    case RELEASED: {
                        Serial.println("(DEBUG) SCAN RELEASED! ");
                        p_parent->updateDeviceState(e_DATE);
                        break;
                    }
                }
                break;
            }
        }
    }

    //KeypadDate:
}
