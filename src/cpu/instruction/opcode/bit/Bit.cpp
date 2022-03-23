#include "Bit.h"

Bit::Bit(unsigned char bit, RegisterName registerName) : bit(bit), registerName(registerName){}

void Bit::execute(Memory& ram, Registers& registers){
    unsigned char valueRegister = registers.getRegister(registerName);

    registers.setFlagZ((valueRegister >> bit) & 0b00000001);
    registers.setFlagN(0);
    registers.setFlagH(1);
}

unsigned int Bit::getSize(){
    return 2;
}

unsigned int Bit::getTiming(){
    return 8;
}

void Bit::setParameters(const Memory&, unsigned short){

}