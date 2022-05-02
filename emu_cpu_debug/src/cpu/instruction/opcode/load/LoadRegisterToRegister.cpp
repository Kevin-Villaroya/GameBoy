#include "LoadRegisterToRegister.h"

LoadRegisterToRegister::LoadRegisterToRegister(RegisterName dest, RegisterName src) : src(src), dest(dest){}

void LoadRegisterToRegister::execute(Memory& ram, Registers& registers){
    registers.setRegister(dest, registers.getRegister(src));
}

unsigned int LoadRegisterToRegister::getSize(){
    return 1;
}

unsigned int LoadRegisterToRegister::getTiming(){
    return 4;
}

void LoadRegisterToRegister::setParameters(Memory&, unsigned short){

}

std::string LoadRegisterToRegister::toString(){
    return "LD " + Registers::getRegisterName(this->dest) + ", " + Registers::getRegisterName(this->src);
}