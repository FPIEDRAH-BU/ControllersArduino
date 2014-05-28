#ifndef PS3CONTROLLER_H
#define PS3CONTROLLER_H

//Local Includes
#include <Controller.h>
#include <Algorithms.h>

//Lib includes
#include <../USB_Host_Shield/PS3Enums.h>


/************************************************
 *              Controller Class                *
 ************************************************
 *-Class Type: Concrete Class of virtual        *
 * Controller class                             *
 ************************************************
 *-Class Description: this class may cast a     *
 * PS3USB object reference or a PS3BT object    *
 * reference, by doing this the library can use *
 * all functions of both objects, this library  *
 * generates middle ware access to the functions*
 * simplifying them.                            *
 ************************************************/
template <typename ps3Ctrl>
class ControllerPs3 : public Controller {
    public:
        ControllerPs3 (USB *usb, ps3Ctrl *ctrl);
        bool connected ();
        double* getAngle ();
        bool* getButtons ();
        int16_t getButtons16Bit ();
        int16_t* getHats ();
        bool hasChanged();
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

    private:
        ps3Ctrl &ctrl;
        static const int numButts = 14;
        const static ButtonEnum buttons [numButts];

        static const int numHats = 4;
        const static AnalogHatEnum hats [numHats];

        static const int numAngs = 2;
        const static AngleEnum angles [numAngs];

        static const int tempBuffSize = 5;
        int16_t *tempBuff;
        bool hasChangedVar;

};


/************************************************
 *                  Button Array                *
 ************************************************
 *-Variable Description:This variable contains a*
 * reference to all the object of ButtonEnum    *
 * that we are interested in for the PS3        *
 * controller.                                  *
 ************************************************/
template <typename ps3Ctrl>
const ButtonEnum ControllerPs3 <ps3Ctrl> ::buttons [numButts] =
    {UP, RIGHT, DOWN, LEFT, TRIANGLE, CIRCLE,
        CROSS, SQUARE, L2, R2, L1, R1, SELECT, START};


/************************************************
 *                   Button Hats                *
 ************************************************
 *-Variable Description:This variable contains a*
 * reference to all the object of AnalogHatEnum *
 * that we are interested in for the PS3        *
 * controller.                                  *
 ************************************************/
template <typename ps3Ctrl>
const AnalogHatEnum ControllerPs3 <ps3Ctrl> ::hats [numHats] =
    {LeftHatX, RightHatX, LeftHatX, LeftHatY};


/************************************************
 *                Button Hats                   *
 ************************************************
 *-Variable Description:This variable contains a*
 * reference to all the object of AngleEnum     *
 * that we are interested in for the PS3        *
 * controller.                                  *
 ************************************************/
template <typename ps3Ctrl>
const AngleEnum ControllerPs3 <ps3Ctrl> ::angles [numAngs] =
    {Pitch, Roll};


/************************************************
 *           Controller Constructor             *
 ************************************************
 *-Function Description: This will initialize   *
 * the Controller reference object and store it *
 * as a private member of the class, as well as *
 * calling the Controller supertype  to work    *
 * with the USB reference object.               *
 ************************************************/
template <typename ps3Ctrl>
ControllerPs3 <ps3Ctrl> ::ControllerPs3 (USB *usb, ps3Ctrl *ctrl) : Controller (usb), ctrl (*ctrl)
{
        tempBuff = (int16_t*) calloc (tempBuffSize, sizeof(int16_t));
        hasChangedVar = false;
}


/************************************************
 *            Controller Constructor            *
 ************************************************
 *-Function Description: The function returns   *
 *true if the controller is ready to be used and*
 *is connected if that is not the case it will  *
 *return false.                                 *
 ************************************************/
template <typename ps3Ctrl>
bool ControllerPs3 <ps3Ctrl>::connected ()
{
    usb.Task();
    return (ctrl.PS3Connected || ctrl.PS3NavigationConnected);
}


/************************************************
 *             Controller Constructor           *
 ************************************************
 *-Function Description: This function will     *
 * return an array with the lectures of the     *
 * angles found in the control, the array will  *
 * have a longitude of numAngs, this length can *
 * be obtained by calling the getNumAng function*
 ************************************************/
template <typename ps3Ctrl>
double* ControllerPs3 <ps3Ctrl> ::getAngle ()
{
    double *states = (double *) calloc(numAngs, sizeof(double));
    if(connected()){
        for(int index = 0; index < numButts; index++)
            states[index] = ctrl.getAngle(angles [index]);
    }

    return states;
}


/************************************************
 *       Controller Constructor                 *
 ************************************************
 *-Function Description: This function will     *
 * return an array with the lectures of the     *
 * buttons found in the control, the array will *
 * have a longitude of numButts, this length can*
 * be obtained by calling the getNumButts       *
 * function                                     *
 ************************************************/
template <typename ps3Ctrl>
bool* ControllerPs3 <ps3Ctrl> ::getButtons ()
{
    bool* states = (bool *) calloc(numButts, sizeof(bool));
    if(connected()){
        for(int index = 0; index < numButts; index++)
            states[index] = ctrl.getButtonClick(buttons [index]);
    }

    fromBitArrayToInt(states, numButts) != tempBuff[0] ?
        tempBuff[0] = fromBitArrayToInt(states, numButts), hasChangedVar = true:
        hasChangedVar = false;

    return states;
}

template <typename ps3Ctrl>
int16_t ControllerPs3 <ps3Ctrl> ::getButtons16Bit (){
    bool *states = getButtons();
    int16_t butts = fromBitArrayToInt(states, this->getNumButts());
    delete (states);

    return butts;
}

/************************************************
 *           Controller Constructor             *
 ************************************************
 *-Function Description: This function will     *
 * return an array with the lectures of the     *
 * hats found in the control, the array will    *
 * have a longitude of numHats, this length can *
 * be obtained by calling the getNumHats        *
 * functions                                    *
 ************************************************/
template <typename ps3Ctrl>
int16_t* ControllerPs3 <ps3Ctrl> ::getHats ()
{
    int16_t* states = (int16_t *) calloc(numHats, sizeof(int16_t));
    if(connected()){
        for(int index = 0; index < numHats; index++){
            states[index] = ctrl.getAnalogHat(hats [index]);
            states[index] != tempBuff[index + 1] ?
                tempBuff[index + 1] = states[index], hasChangedVar = true:
                hasChangedVar = false;
        }
    }
    return states;
}


template <typename ps3Ctrl>
bool ControllerPs3 <ps3Ctrl> ::hasChanged ()
{
    return hasChangedVar;
}

#endif
