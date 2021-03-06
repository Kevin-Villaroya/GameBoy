#include "PopStackToDoubleRegister.h"
#include <iostream>

PopStackToDoubleRegister::PopStackToDoubleRegister(DoubleRegisterName r):doubleRegName(r){}

void PopStackToDoubleRegister::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();
    unsigned short doubleRegVal = 0;
    
    doubleRegVal = ram.get(spValue+1);
    doubleRegVal <<= 8;
    doubleRegVal += ram.get(spValue);
    registers.setSP(spValue+2);
    registers.setDoubleRegister(doubleRegName, doubleRegVal);
}

unsigned int PopStackToDoubleRegister::getSize(){
    return 1;
}

unsigned int PopStackToDoubleRegister::getTiming(){
    return 12;
}

void PopStackToDoubleRegister::setParameters(Memory&, unsigned short){
}

std::string PopStackToDoubleRegister::toString(){
    return "POP " + Registers::getDoubleRegisterName(this->doubleRegName);
}