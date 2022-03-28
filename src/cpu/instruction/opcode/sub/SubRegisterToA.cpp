#include "SubRegisterToA.h"

SubRegisterToA::SubRegisterToA(RegisterName registerName) : registerName(registerName){}

void SubRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char aValue = registers.getA();

    if(regValue-aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (regValue & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < regValue)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - regValue);
}

unsigned int SubRegisterToA::getSize(){
    return 1;
}

unsigned int SubRegisterToA::getTiming(){
    return 4;
}

void SubRegisterToA::setParameters(const Memory&, unsigned short){

}

std::string SubRegisterToA::toString(){
    return "SUB " + Registers::getRegisterName(this->registerName);
}