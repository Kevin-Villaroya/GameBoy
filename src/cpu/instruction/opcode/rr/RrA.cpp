#include "RrA.h"

RrA::RrA(){}

void RrA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    unsigned char valueOf0bit = aValue&0b00000001;
    aValue >>= 1;
    aValue += (registers.isFlagC()?1:0)<<7;
    if(aValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    registers.setA(aValue);
}

unsigned int RrA::getSize(){
    return 1;
}

unsigned int RrA::getTiming(){
    return 4;
}

void RrA::setParameters(const Memory&, unsigned short v){
}
