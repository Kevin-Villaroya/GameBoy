#include "Bit.h"

Bit::Bit(unsigned char bit, RegisterName registerName) : bit(bit), registerName(registerName){}

void Bit::execute(Memory& ram, Registers& registers){
    unsigned char valueRegister = registers.getRegister(registerName);

    registers.setFlagZ(!(valueRegister & (1<<this->bit)));
    registers.setFlagN(0);
    registers.setFlagH(1);
}

unsigned int Bit::getSize(){
    return 2;
}

unsigned int Bit::getTiming(){
    return 8;
}

void Bit::setParameters(Memory&, unsigned short){

}

std::string Bit::toString(){
    return "BIT " + std::to_string(((int)this->bit)) + "," + Registers::getRegisterName(this->registerName);
}