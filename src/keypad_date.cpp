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
    _keypad.addEventListener(keypad_event); //provide function pointer to be called when a
    //change of keystate occurs.
}

char KeypadDate::listen_for_key() {
    return _keypad.getKey();
}

//callback function from keypad
static void KeypadDate::keypad_event(char key, KeypadDate* keypadDate) {
    KeyState keyState = keypadDate->_keypad.getState();
    if (keyState != IDLE) {
        switch (key) {
            case '1': keypadDate->key_one(keyState);break;
            case '2': keypadDate->key_two(keyState);break;
            case '3': keypadDate->key_three(keyState);break;
            case '4': keypadDate->key_four(keyState);break;
            case '5': keypadDate->key_five(keyState);break;
            case '6': keypadDate->key_six(keyState);break;
            case '7': keypadDate->key_seven(keyState);break;
            case '8': keypadDate->key_eight(keyState);break;
            case '9': keypadDate->key_nine(keyState);break;
            case '0': keypadDate->key_zero(keyState);break;
            case '*': keypadDate->key_star(keyState);break;
            case '#': keypadDate->key_hash(keyState);break;
        }
    }
}

void KeypadDate::append_lockcode(char key) {
    if (_code.length() < 4) {
        _code += key;
    }
}

void KeypadDate::append_date(char key) {
    if (_date.length() < 6) {
        _date += key;
    }
}

bool KeypadDate::is_valid() {
    return true;
}

void KeypadDate::key_one(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('1');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('1');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_two(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('2');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('2');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
        case LIST: {
            switch (keyState) {
                case PRESSED: {
                    
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_three(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('3');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('3');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_four(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('4');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('4');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_five(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('5');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('5');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_six(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('6');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('6');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_seven(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('7');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('7');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_eight(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('8');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('8');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_nine(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('9');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('9');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_zero(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    append_lockcode('0');
                    Serial.println(_code);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    append_date('0');
                    Serial.println(_date);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_star(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    _parent->update_device_state(LOCK);
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case PRESSED: {
                    _parent->update_device_state(DATE);
                    break;
                }
                case HOLD: {
                    _parent->update_device_state(LIST);
                    break;
                }
            }
            break;
        }
        case LIST: {
            switch (keyState) {
                case HOLD: {
                    _parent->update_device_state(DATE);
                    break;
                }
            }
            break;
        }
    }
}

void KeypadDate::key_hash(KeyState keyState) {
    switch (_parent->get_state()) {
        case LOCK: {
            switch (keyState) {
                case PRESSED: {
                    if (_code.equals(_correctCode)) {
                        Serial.println(F("CORRECT CODE "));
                        _parent->update_device_state(DATE);
                    } else {
                        Serial.println(F("INVALID CODE "));
                        _parent->update_device_state(LOCK);
                    }
                    break;
                }
            }
            break;
        }
        case DATE: {
            switch (keyState) {
                case HOLD: {
                    if (is_valid()) {
                        Serial.println(F("(DEBUG) VALID DATE "));
                        _parent->update_device_state(SCAN);
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
                    _parent->update_device_state(DATE);
                    break;
                }
            }
            break;
        }
    }
}
}
