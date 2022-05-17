#include "SubImmediateToA.h"
#include "../../util/DecToHex.h"
#include <iostream>

void SubImmediateToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    if(aValue - this->parameter == 0){
        registers.setFlagZ(1);
    }
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (this->parameter & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < this->parameter)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - this->parameter);
}

unsigned int SubImmediateToA::getSize(){
    return 2;
}

unsigned int SubImmediateToA::getTiming(){
    return 8;
}

void SubImmediateToA::setParameters(Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string SubImmediateToA::toString(){
    return "SUB " + charToHex(this->parameter);
}