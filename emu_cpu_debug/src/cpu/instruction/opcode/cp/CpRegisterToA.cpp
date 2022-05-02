#include "CpRegisterToA.h"

CpRegisterToA::CpRegisterToA(RegisterName r):registerName(r){}

void CpRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getRegister(registerName);
    unsigned char aVal = registers.getRegister(RegisterName::A);

    if(regVal == aVal)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    
    registers.setFlagN(1);
    
    if((aVal & 0b00001111) < (regVal & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aVal < regVal)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
}

unsigned int CpRegisterToA::getSize(){
    return 1;
}

unsigned int CpRegisterToA::getTiming(){
    return 4;
}

void CpRegisterToA::setParameters(Memory&, unsigned short){
}

std::string CpRegisterToA::toString(){
    return "CP " + Registers::getRegisterName(this->registerName);
}