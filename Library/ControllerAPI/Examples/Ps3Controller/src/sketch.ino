#include <PS3USB.h>
#include <usbhub.h>
#include <PS3Controller.h>

USB Usb;
PS3USB PS3(&Usb); // This will just create the instance
ControllerPs3 <PS3USB> ctrl(&Usb, &PS3);

void setup(){
  ctrl.setUp();
}


void loop()
{
    int16_t* hats = ctrl.getHats();
    bool changedHats = ctrl.hasChanged();

    int16_t butts = ctrl.getButtons16Bit();
    bool changedButtons = ctrl.hasChanged();

    if(changedButtons)
        Serial.println("Buttons Changed");

    if(changedHats)
        Serial.println("Changed Hats");

    delete (hats);
}

