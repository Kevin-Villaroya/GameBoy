#include "OrRegisterToA.h"

OrRegisterToA::OrRegisterToA(RegisterName r):registerName(r){}

void OrRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getRegister(registerName);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(regVal | aVal);

    if((regVal | aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(0);
}

unsigned int OrRegisterToA::getSize(){
    return 1;
}

unsigned int OrRegisterToA::getTiming(){
    return 4;
}

void OrRegisterToA::setParameters(Memory&, unsigned short){
}

std::string OrRegisterToA::toString(){
    return "OR " + Registers::getRegisterName(this->registerName);
}