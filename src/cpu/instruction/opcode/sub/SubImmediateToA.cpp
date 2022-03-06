#include "SubImmediateToA.h"

SubImmediateToA::SubImmediateToA(){}

void SubImmediateToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();

    if(this->parameter-aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue&0b00001111) < (this->parameter&0b00001111))
        registers.setFlagH(0);
    else
        registers.setFlagH(1);

    if(aValue < this->parameter)
        registers.setFlagC(0);
    else
        registers.setFlagC(1);
    
    registers.setFlagN(1);
}

unsigned int SubImmediateToA::getSize(){
    return 2;
}

unsigned int SubImmediateToA::getTiming(){
    return 8;
}

void SubImmediateToA::setParameters(const Memory&, unsigned short v){
    this->parameter = v;
}