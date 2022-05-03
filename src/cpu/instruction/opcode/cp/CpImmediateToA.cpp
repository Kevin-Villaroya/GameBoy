#include "CpImmediateToA.h"
#include "../../util/DecToHex.h"
#include <iostream>

CpImmediateToA::CpImmediateToA(){}

void CpImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);

    if(this->parameter == aVal)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(1);
    
    if((aVal & 0b00001111) < (this->parameter & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aVal < this->parameter)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
}

unsigned int CpImmediateToA::getSize(){
    return 2;
}

unsigned int CpImmediateToA::getTiming(){
    return 8;
}

void CpImmediateToA::setParameters(Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string CpImmediateToA::toString(){
    return "CP " + charToHex(this->parameter);
}