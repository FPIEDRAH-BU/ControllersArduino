#include <Controller.h>


Controller::Controller(USB *usb) : usb(*usb){}


void Controller::setUp(){
    Serial.begin(115200);
    while(!Serial);

    if(usb.Init() == -1){
        Serial.print("Failed to start USB");
    }
}


