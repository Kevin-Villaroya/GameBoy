#include "RrCarryA.h"

RrCarryA::RrCarryA(){}

void RrCarryA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    unsigned char valueOf0bit = aValue&0b00000001;
    aValue >>= 1;
    aValue += valueOf0bit<<7;

    if(aValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    registers.setA(aValue);
}

unsigned int RrCarryA::getSize(){
    return 1;
}

unsigned int RrCarryA::getTiming(){
    return 4;
}

void RrCarryA::setParameters(const Memory&, unsigned short v){
}