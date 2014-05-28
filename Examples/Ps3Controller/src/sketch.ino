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
    Usb.Task();

    bool* butts = ctrl.getButtons();
    if(butts[0])
        Serial.println("Up");
    if(butts[1])
        Serial.println("Right");

    delete (butts);
}

