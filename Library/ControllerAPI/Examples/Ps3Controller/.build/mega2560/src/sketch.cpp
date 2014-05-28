#include <Arduino.h>
#include <PS3USB.h>
#include <usbhub.h>
#include <PS3Controller.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <PS3USB.h>
//#include <usbhub.h>
//#include <PS3Controller.h>

USB Usb;
PS3USB PS3(&Usb); // This will just create the instance
ControllerPs3 <PS3USB> ctrl(&Usb, &PS3);

void setup(){
  ctrl.setUp();
}


void loop()
{
    int16_t* hats = ctrl.getHats();

    int16_t butts = ctrl.getButtons16Bit();
    int16_t leftHatX = hats[0];
    int16_t rightHatX = hats[1];
    int16_t leftHatY = hats [2];
    int16_t rightHatY = hats [3];

    if(ctrl.hasChanged()){
        Serial.println("Send Data");
    }

    delete (hats);
}

