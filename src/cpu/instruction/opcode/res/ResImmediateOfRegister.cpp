#include "ResImmediateOfRegister.h"
#include "../../util/DecToHex.h"
#include <math.h>

ResImmediateOfRegister::ResImmediateOfRegister(unsigned char bit, RegisterName registerName) : bit(bit), registerName(registerName){}

void ResImmediateOfRegister::execute(Memory& ram, Registers& registers){
    unsigned char valueRegister = registers.getRegister(this->registerName);

    valueRegister &= 255 - (unsigned char)pow(2, bit);

    registers.setRegister(this->registerName, valueRegister);
}

unsigned int ResImmediateOfRegister::getSize(){
    return 2;
}

unsigned int ResImmediateOfRegister::getTiming(){
    return 8;
}

void ResImmediateOfRegister::setParameters(const Memory&, unsigned short){
}

std::string ResImmediateOfRegister::toString(){
    return "RES " + std::to_string((int)this->bit) + ", " + Registers::getRegisterName(this->registerName);
}