#include "IncrementDoubleRegister.h"

IncrementDoubleRegister::IncrementDoubleRegister(DoubleRegisterName registerName) : registerName(registerName){}

void IncrementDoubleRegister::execute(Memory& ram, Registers& registers){
    registers.setDoubleRegister(this->registerName, registers.getDoubleRegister(this->registerName) + 1);
}

unsigned int IncrementDoubleRegister::getSize(){
    return 1;
}

unsigned int IncrementDoubleRegister::getTiming(){
    return 8;
}

void IncrementDoubleRegister::setParameters(const Memory&, unsigned short){

}

std::string IncrementDoubleRegister::toString(){
    return "INC " + Registers::getDoubleRegisterName(this->registerName);
}