#ifndef PS3CONTROLLER_H
#define PS3CONTROLLER_H

//Local Includes
#include <Controller.h>

//Lib includes
#include <../USB_Host_Shield/XBOXUSB.h>

class XboxController : public Controller {
    public:
        XboxController(USB *usb, XBOXUSB *ctrl);
        bool connected ();
        double* getAngle ();
        bool* getButtons ();
        uint16_t* getHats ();
        bool hasChanged ();

        int getNumButts()
        {
            return numButts;
        }

        int getNumAngles()
        {
            return numAngs;
        }

        int getNumHats()
        {
            return numHats;
        }

        int getTemBuffSize()
        {
            return tempBuffSize;
        }

    private:
        XBOXUSB &ctrl;
        static const int numButts = 15;
        const static ButtonEnum buttons [numButts];

        static const int numHats = 4;
        const static AnalogHatEnum hats [numHats];

        static const int numAngs = 0;
        const static AngleEnum angles [numAngs];

        static const int tempBuffSize = 5;
        int16_t *tempBuff;
        bool hasChangedVar;
};

#endif
