#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define INT_SIZE 16

#include <Arduino.h>

int16_t fromBitArrayToInt (bool *BitArray, int size){
    byte loByte, hiByte;

    if(size > INT_SIZE)
        return -1;

    for (int index = 0; index < INT_SIZE/2; index++){
        if(index < size)
            bitWrite(loByte, index, BitArray[index]);
        else
            bitWrite(loByte, index, 0);

        if(index + 8 < size)
            bitWrite(hiByte, index, BitArray[index + 8]);
        else
            bitWrite(hiByte, index, 0);
    }

    return (int16_t) word(loByte, hiByte);
}

#endif
