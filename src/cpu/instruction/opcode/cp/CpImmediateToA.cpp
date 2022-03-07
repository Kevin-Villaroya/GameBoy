#include "CpImmediateToA.h"

CpImmediateToA::CpImmediateToA(){}

void CpImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(this->parameter&aVal);

    if(this->parameter == aVal)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    if((aVal&0b00001111) < (this->parameter&0b00001111))
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

void CpImmediateToA::setParameters(const Memory& m, unsigned short v){
    this->parameter = v;
}