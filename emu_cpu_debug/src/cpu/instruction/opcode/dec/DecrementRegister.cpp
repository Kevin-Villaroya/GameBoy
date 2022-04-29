#include "DecrementRegister.h"
#include <iostream>

DecrementRegister::DecrementRegister(RegisterName registerName) : registerName(registerName){}

void DecrementRegister::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getRegister(this->registerName);
    unsigned char nvalue = regVal - 1;

    registers.setRegister(this->registerName, nvalue);

    if(regVal>>4 != nvalue>>4){
        registers.setFlagH(1);
    }else{
        registers.setFlagH(0);
    }

    if(nvalue == 0){
        registers.setFlagZ(1);
    }else{
        registers.setFlagZ(0);
    }

    registers.setFlagN(true);

}

unsigned int DecrementRegister::getSize(){
    return 1;
}

unsigned int DecrementRegister::getTiming(){
    return 4;
}

void DecrementRegister::setParameters(const Memory&, unsigned short){

}

std::string DecrementRegister::toString(){
    return "DEC " + Registers::getRegisterName(this->registerName);
}