#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define INT_SIZE

#include <Arduino.h>

int16_t fromBitArrayToInt (bool *BitArray, int size){
    byte loByte, hiByte;

    if(size > 16)
        return -1;

    for (int index = 0; index < INT_SIZE; index++){
        if(index < size)
            bitWrite(loByte, BitArray[index]);
        else
            bitWrite(loByte, 0);

        if(index + 8 < size)
            bitWrite(hiByte, BitArray[index + 8]);
        else
            bitWrite(hiByte, 0);
    }

    return (int16_t) word(hiByte, loByte);
}

#endif
