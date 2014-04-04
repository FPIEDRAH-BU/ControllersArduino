#ifndef CONTROLLER_H
#define CONTROLLER_H

//Arduino compiler includes
#include <Arduino.h>

//Lib includes
#include <../USB_Host_Shield/Usb.h>
#include <../USB_Host_Shield/controllerEnums.h>


/************************************************
 *              Controller Class                *
 ************************************************
 *-Class Type: Virtual Base Class               *
 ************************************************
 *-Class Description: Structure definition to   *
 * add functions and simplify the  host USB     *
 * controller classes.                          *
 ************************************************/
class Controller {
    public:
        Controller (USB *usb);
        virtual bool connected () = 0;
        virtual double* getAngle () = 0;
        virtual bool* getButtons () = 0;
        virtual uint16_t* getHats () = 0;
        virtual bool hasChanged() = 0;

        void setUp();

    protected:
        USB &usb;
        const static ButtonEnum buttons [];
        const static AnalogHatEnum hats [];
        const static AngleEnum angles [];

        static const int numButts;
        static const int numHats;
        static const int numAngs;
        static const int tempBuffSize;

};


#endif
