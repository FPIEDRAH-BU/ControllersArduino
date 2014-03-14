#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

#include <../USB_Host_Shield/Wii.h>
#include <../USB_Host_Shield/XBOXUSB.h>
#include <../USB_Host_Shield/PS3Enums.h>
#include <../USB_Host_Shield/controllerEnums.h>


class Controller {
    public:
        Controller (USB *usb);
        virtual bool connected () = 0;
        virtual double* getAngle () = 0;
        virtual bool* getButtons () = 0;
        virtual uint8_t* getHats () = 0;

        int getNumButts(){return numButts;}
        int getNumAngles(){return numAngs;}
        int getNumHats(){return numHats;}

        void setUp();

    protected:
        USB &usb;
        const static ButtonEnum buttons [];
        const static AnalogHatEnum hats [];
        const static AngleEnum angles [];

        static const int numButts;
        static const int numHats;
        static const int numAngs;
};



#endif
