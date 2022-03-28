#include "RlRegister.h"

RlRegister::RlRegister(RegisterName r):registerName(r){}

void RlRegister::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char valueOf7bit = regValue>>7;
    regValue <<= 1;
    regValue += registers.isFlagC()?1:0;
    if(regValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    registers.setRegister(registerName, regValue);
}

unsigned int RlRegister::getSize(){
    return 2;
}

unsigned int RlRegister::getTiming(){
    return 8;
}

void RlRegister::setParameters(const Memory&, unsigned short v){
}

std::string RlRegister::toString(){
    return "RL " + Registers::getRegisterName(this->registerName);
}