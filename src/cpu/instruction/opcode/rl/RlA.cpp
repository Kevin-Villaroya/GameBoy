#include "RlA.h"

RlA::RlA(){}

void RlA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    unsigned char valueOf7bit = aValue>>7;
    aValue <<= 1;
    aValue += registers.isFlagC()?1:0;
    if(aValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    registers.setA(aValue);
}

unsigned int RlA::getSize(){
    return 1;
}

unsigned int RlA::getTiming(){
    return 4;
}

void RlA::setParameters(const Memory&, unsigned short v){
}
