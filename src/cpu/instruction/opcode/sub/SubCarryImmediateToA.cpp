#include "SubCarryImmediateToA.h"

SubCarryImmediateToA::SubCarryImmediateToA(){}

void SubCarryImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aValue = registers.getA()+(registers.isFlagC()?1:0);

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

unsigned int SubCarryImmediateToA::getSize(){
    return 2;
}

unsigned int SubCarryImmediateToA::getTiming(){
    return 8;
}

void SubCarryImmediateToA::setParameters(const Memory&, unsigned short v){
    this->parameter = v;
}