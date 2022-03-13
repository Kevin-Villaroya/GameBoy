#include "RlCarryA.h"

RlCarryA::RlCarryA(){}

void RlCarryA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    unsigned char valueOf7bit = aValue>>7;
    aValue <<= 1;
    aValue += valueOf7bit;

    if(aValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    registers.setA(aValue);
}

unsigned int RlCarryA::getSize(){
    return 1;
}

unsigned int RlCarryA::getTiming(){
    return 4;
}

void RlCarryA::setParameters(const Memory&, unsigned short v){
}