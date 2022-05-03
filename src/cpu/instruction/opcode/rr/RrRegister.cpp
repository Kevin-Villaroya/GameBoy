#include "RrRegister.h"

RrRegister::RrRegister(RegisterName r):registerName(r){}

void RrRegister::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    bool valueOf0bit = regValue&0b00000001;
    regValue >>= 1;
    regValue += ((unsigned char)(registers.isFlagC()?1:0))<<7;
    if(regValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    registers.setRegister(registerName, regValue);
}

unsigned int RrRegister::getSize(){
    return 2;
}

unsigned int RrRegister::getTiming(){
    return 8;
}

void RrRegister::setParameters(Memory&, unsigned short v){
}

std::string RrRegister::toString(){
    return "RR " + Registers::getRegisterName(this->registerName);
}