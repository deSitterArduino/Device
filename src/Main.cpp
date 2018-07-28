//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "device.h"

device_lib::Device device;

void setup() {
    Serial.begin(9600);
    Serial.print(F("Type any character to start\n"));
    while (!Serial.available()) {
        //do nothing
    }
    //device.temp();
}

void loop() {

device.listen_for_key();

}
