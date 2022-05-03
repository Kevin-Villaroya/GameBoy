#include "RrCarryRegister.h"

RrCarryRegister::RrCarryRegister(RegisterName r):registerName(r){}

void RrCarryRegister::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char valueOf0bit = regValue&0b00000001;
    regValue >>= 1;
    regValue += valueOf0bit<<7;

    if(regValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    registers.setRegister(registerName, regValue);
}

unsigned int RrCarryRegister::getSize(){
    return 2;
}

unsigned int RrCarryRegister::getTiming(){
    return 8;
}

void RrCarryRegister::setParameters(Memory&, unsigned short v){
}

std::string RrCarryRegister::toString(){
    return "RRC " + Registers::getRegisterName(this->registerName);
}