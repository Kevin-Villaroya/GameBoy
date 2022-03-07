#include "XorImmediateToA.h"

XorImmediateToA::XorImmediateToA(){}

void XorImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(this->parameter&aVal);

    if(this->parameter^aVal == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    registers.setFlagC(0);
    registers.setFlagH(1);
}

unsigned int XorImmediateToA::getSize(){
    return 2;
}

unsigned int XorImmediateToA::getTiming(){
    return 8;
}

void XorImmediateToA::setParameters(const Memory& m, unsigned short v){
    this->parameter = v;
}