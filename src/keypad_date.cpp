//**************************************************************************************************
//    KeypadDate.cpp - Wrapper of M. Stanley amd A. Brevig's Keypad Libiary v3.1
//    Changed callback eventListener function's arguments to include a pointer to
//    the instance of this class to which the instance of the Keypad object calling eventListener
//    belongs. This is for the purpose of referencing non-static members directly from the static
//    callback function.
//
//    Used to read key-presses from a 3x4 matrix keypad and produce valid dates from the input.
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "keypad_date.h"
#include "device.h"
//definition required for access to parent 'Device class' through parent pointer '_parent'

namespace device_lib {

KeypadDate::KeypadDate(Device* parent)
    :_parent(parent), _keypad{Keypad(makeKeymap(keys), _rowPins, _colPins, _ROWS, _COLS, this)}
{
    _keypad.addEventListener(keypadEvent); //provide function pointer to be called when a
    //change of keystate occurs.
}

char KeypadDate::listenForKey() {
    return _keypad.getKey();
}

//callback function from keypad
static void KeypadDate::keypadEvent(char key, KeypadDate* keypadDate) {
    KeyState keyState = keypadDate->_keypad.getState();
    if (keyState != IDLE) {
        switch (key) {
            case '1': keypadDate->keyOne(keyState);break;
            case '2': keypadDate->keyTwo(keyState);break;
            case '3': keypadDate->keyThree(keyState);break;
            case '4': keypadDate->keyFour(keyState);break;
            case '5': keypadDate->keyFive(keyState);break;
            case '6': keypadDate->keySix(keyState);break;
            case '7': keypadDate->keySeven(keyState);break;
            case '8': keypadDate->keyEight(keyState);break;
            case '9': keypadDate->keyNine(keyState);break;
            case '0': keypadDate->keyZero(keyState);break;
            case '*': keypadDate->keyStar(keyState);break;
            case '#': keypadDate->keyHash(keyState);break;
        }
    }
}

void KeypadDate::addToLockCode(char key) {
    if (_inputCode.length() < 4) {
        _inputCode += key;
    }
}

void KeypadDate::addToDate(char key) {
    if (_inputDate.length() < 6) {
        _inputDate += key;
    }
}

bool KeypadDate::isValid() {
    return true;
}

void KeypadDate::keyOne(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('1');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('1');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyTwo(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('2');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('2');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyThree(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('3');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('3');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyFour(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('4');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('4');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyFive(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('5');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('5');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keySix(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('6');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('6');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keySeven(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('7');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('7');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyEight(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('8');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('8');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyNine(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('9');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('9');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyZero(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    addToLockCode('0');
                    Serial.println(_inputCode);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    addToDate('0');
                    Serial.println(_inputDate);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyStar(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    _parent->updateDeviceState(LOCK);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    _parent->updateDeviceState(DATE);
                    break;
                }
                case HOLD: {
                    _parent->updateDeviceState(LIST);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::keyHash(KeyState keyState) {
    switch (_parent->getState()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    if (_inputCode.equals(_correctCode)) {
                        Serial.println(F("CORRECT CODE "));
                        _parent->updateDeviceState(DATE);
                    } else {
                        Serial.println(F("INVALID CODE "));
                        _parent->updateDeviceState(LOCK);
                    }
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case HOLD: {
                    if (isValid()) {
                        Serial.println(F("(DEBUG) VALID DATE "));
                        _parent->updateDeviceState(SCAN);
                    }
                    break;
                }
            }
            break;
        }
        case SCAN: {
            switch (keyState) {
                case RELEASED: {
                    Serial.println(F("(DEBUG) SCAN RELEASED! "));
                    _parent->updateDeviceState(DATE);
                    break;
                }
            }
            break;
        }
    }
}
}
