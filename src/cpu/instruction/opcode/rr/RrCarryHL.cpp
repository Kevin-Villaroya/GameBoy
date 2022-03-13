#include "RrCarryHL.h"

RrCarryHL::RrCarryHL(){}

void RrCarryHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char memValue = ram.get(hlValue);
    unsigned char valueOf0bit = memValue&0b00000001;
    memValue >>= 1;
    memValue += valueOf0bit<<7;

    if(memValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    ram.set(hlValue, memValue);
}

unsigned int RrCarryHL::getSize(){
    return 2;
}

unsigned int RrCarryHL::getTiming(){
    return 16;
}

void RrCarryHL::setParameters(const Memory&, unsigned short v){
}