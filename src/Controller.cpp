#include <Controller.h>

/************************************************
 *	           Controller Constructor	        *
 ************************************************
 *-Function Description: Initializes the USB    *
 * reference from the USB Shield library        *
 ************************************************/
Controller::Controller(USB *usb) : usb(*usb){}


/************************************************
 *	         Controller SetUp function	        *
 ************************************************
 *-Function Description: this function must be 	*
 * called in the setup function of the arduino 	*
 * sketch, this setups the USB reference object.*
 ************************************************
 *-Exceptions: This function returns an error in*
 * the serial port if it fails initializing the *
 * USB reference object, in this error situation*
 * the arduino will end up in an infinite loop. *
 ************************************************/
void Controller::setUp(){
    Serial.begin(115200);
    while(!Serial);

    if(usb.Init() == -1){
        Serial.print("Failed to start USB");
	while(true);
    }
}


