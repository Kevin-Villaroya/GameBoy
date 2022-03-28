#include "RlCarryRegister.h"

RlCarryRegister::RlCarryRegister(RegisterName r):registerName(r){}

void RlCarryRegister::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char valueOf7bit = regValue>>7;
    regValue <<= 1;
    regValue += valueOf7bit;

    if(regValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    registers.setRegister(registerName, regValue);
}

unsigned int RlCarryRegister::getSize(){
    return 2;
}

unsigned int RlCarryRegister::getTiming(){
    return 8;
}

void RlCarryRegister::setParameters(const Memory&, unsigned short v){
}

std::string RlCarryRegister::toString(){
    return "RLC " + Registers::getRegisterName(this->registerName);
}