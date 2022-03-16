#include "OrImmediateToA.h"

OrImmediateToA::OrImmediateToA(){}

void OrImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(this->parameter | aVal);

    if((this->parameter | aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagC(0);
    registers.setFlagH(0);
}

unsigned int OrImmediateToA::getSize(){
    return 2;
}

unsigned int OrImmediateToA::getTiming(){
    return 8;
}

void OrImmediateToA::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}
