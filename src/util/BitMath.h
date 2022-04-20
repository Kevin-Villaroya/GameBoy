#ifndef __BIT_MATH_H__
#define __BIT_MATH_H__

void setBit(unsigned char& bit, int index);
unsigned char returnSetBit(unsigned char bit, int index);
void resetBit(unsigned char& bit, int index);
unsigned char returnResetBit(unsigned char bit, int index);
bool testBit(unsigned char bit, int index);
unsigned char bitGetVal(unsigned char bit, int index);

#endif