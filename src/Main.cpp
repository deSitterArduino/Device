#include "Device.h"

Device_lib::Device device;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
    char key = device.keypadDate.listenForKey();
    
}



