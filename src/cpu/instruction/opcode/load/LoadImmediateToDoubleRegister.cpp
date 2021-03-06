#include <iostream>
#include "LoadImmediateToDoubleRegister.h"

LoadImmediateToDoubleRegister::LoadImmediateToDoubleRegister(DoubleRegisterName registerName){
    this->registerName = registerName;
}
        
void LoadImmediateToDoubleRegister::execute(Memory& ram, Registers& registers){
    registers.setDoubleRegister(this->registerName, this->parameter);
}

unsigned int LoadImmediateToDoubleRegister::getSize(){
    return 3;
}

unsigned int LoadImmediateToDoubleRegister::getTiming(){
    return 12;
}

void LoadImmediateToDoubleRegister::setParameters(Memory& memory, unsigned short positionParameters){
    this->parameter = memory.getDouble(positionParameters);
}

std::string LoadImmediateToDoubleRegister::toString(){
    return "LD " + Registers::getDoubleRegisterName(this->registerName) + ", " + std::to_string((int)this->parameter);
}