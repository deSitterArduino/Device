//**************************************************************************************************
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "device.h"

device_lib::Device device;

void setup() {
  Serial.begin(9600);
}

void loop() {

device.listenForKey();

}
