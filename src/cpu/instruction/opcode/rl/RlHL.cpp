#include "RlHL.h"

RlHL::RlHL(){}

void RlHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char memValue = ram.get(hlValue);
    unsigned char valueOf7bit = memValue>>7;
    memValue <<= 1;
    memValue += registers.isFlagC()?1:0;
    if(memValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    ram.set(hlValue, memValue);
}

unsigned int RlHL::getSize(){
    return 2;
}

unsigned int RlHL::getTiming(){
    return 16;
}

void RlHL::setParameters(const Memory&, unsigned short v){
}