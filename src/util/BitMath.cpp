#include "BitMath.h"
#include <math.h>

void setBit(unsigned char& bit, int index){
    bit |= (unsigned char)pow(2, index);
}

void resetBit(unsigned char& bit, int index){
    bit &= 255 - (unsigned char)pow(2, index);
}

bool testBit(unsigned char bit, int index){
    return (bit & (1 << index)) != 0;
}