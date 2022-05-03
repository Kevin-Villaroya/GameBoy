#include "SetBitRegister.h"

SetBitRegister::SetBitRegister(int b, RegisterName r):bit(b),registerName(r){}

void SetBitRegister::execute(Memory& ram, Registers& registers){
    unsigned char registerValue = registers.getRegister(registerName);
    unsigned char compare = 0b1<<this->bit;
    registerValue |= compare;
    
    registers.setRegister(registerName, registerValue);
}

unsigned int SetBitRegister::getSize(){
    return 2;
}

unsigned int SetBitRegister::getTiming(){
    return 8;
}

void SetBitRegister::setParameters(Memory&, unsigned short v){
}

std::string SetBitRegister::toString(){
    return "SET " + std::to_string(this->bit) +", "+ Registers::getRegisterName(this->registerName);
}