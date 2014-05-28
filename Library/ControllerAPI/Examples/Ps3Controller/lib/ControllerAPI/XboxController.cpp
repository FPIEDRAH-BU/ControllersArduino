#include <XboxController.h>

const ButtonEnum XboxController::buttons [numButts] =
    {UP, RIGHT, DOWN, LEFT, A, B,
        X, Y, L2, R2, L1, R1, SELECT, START, XBOX};

const AnalogHatEnum XboxController::hats [numHats] =
    {LeftHatX, RightHatX, LeftHatX, LeftHatY};

const AngleEnum XboxController::angles [numAngs] = {};

XboxController::XboxController (USB *usb, XBOXUSB *ctrl) : Controller (usb), ctrl (*ctrl)
{
        tempBuff = (int16_t*) calloc (tempBuffSize, sizeof(int16_t));
        hasChangedVar = false;
}

bool XboxController::hasChanged(){
     return hasChangedVar;
}

bool XboxController::connected ()
{
    usb.Task();
    return (ctrl.Xbox360Connected);
}

double* XboxController::getAngle ()
{
    double *states = (double *) calloc(numAngs, sizeof(double));

    return states;
}

bool* XboxController::getButtons ()
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

int16_t XboxController::getButtons16Bit ()
{
    bool* states = this->getButtons();
    int16_t butts = fromBitArrayToInt(states, this->getNumButts());
    delete (states);

    return butts;
}

int16_t* XboxController::getHats ()
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
