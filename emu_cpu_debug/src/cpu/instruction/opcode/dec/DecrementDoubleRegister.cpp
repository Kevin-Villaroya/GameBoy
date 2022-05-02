#include "DecrementDoubleRegister.h"
#include <iostream>

DecrementDoubleRegister::DecrementDoubleRegister(DoubleRegisterName registerName) : registerName(registerName){}

void DecrementDoubleRegister::execute(Memory& ram, Registers& registers){
    unsigned short value = registers.getDoubleRegister(this->registerName) - 1;

    registers.setDoubleRegister(this->registerName, value);
}

unsigned int DecrementDoubleRegister::getSize(){
    return 1;
}

unsigned int DecrementDoubleRegister::getTiming(){
    return 8;
}

void DecrementDoubleRegister::setParameters(Memory&, unsigned short){

}

std::string DecrementDoubleRegister::toString(){
    return "DEC " + Registers::getDoubleRegisterName(this->registerName);
}