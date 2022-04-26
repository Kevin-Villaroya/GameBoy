#include "IncrementRegister.h"
#include <iostream>

IncrementRegister::IncrementRegister(RegisterName registerName) : registerName(registerName){}

void IncrementRegister::execute(Memory& ram, Registers& registers){
    bool byte3Before = registers.getRegister(this->registerName) & 0b00001000;

    unsigned char value = registers.getRegister(this->registerName) + 1;

    bool byte3After = value & 0b00001000;

    registers.setRegister(this->registerName, value);

    if(byte3Before && !byte3After){
        registers.setFlagH(1);
    }else{
        registers.setFlagH(0);
    }

    if(value == 0){
        registers.setFlagZ(1);
    }else{
        registers.setFlagZ(0);
    }

    registers.setFlagN(0);

}

unsigned int IncrementRegister::getSize(){
    return 1;
}

unsigned int IncrementRegister::getTiming(){
    return 4;
}

void IncrementRegister::setParameters(const Memory&, unsigned short){

}

std::string IncrementRegister::toString(){
    return "INC " + Registers::getRegisterName(this->registerName);
}