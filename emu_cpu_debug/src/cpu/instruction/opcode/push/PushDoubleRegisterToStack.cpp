#include "PushDoubleRegisterToStack.h"
#include <iostream>

PushDoubleRegisterToStack::PushDoubleRegisterToStack(DoubleRegisterName r):doubleRegName(r){}

void PushDoubleRegisterToStack::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();
    unsigned short doubleRegVal = registers.getDoubleRegister(doubleRegName);
    unsigned char leftRegVal = doubleRegVal >> 8;
    unsigned char rightRegVal = doubleRegVal;
    
    ram.writeMemory(spValue-1, leftRegVal);
    ram.writeMemory(spValue-2, rightRegVal);
    registers.setSP(spValue-2);
}

unsigned int PushDoubleRegisterToStack::getSize(){
    return 1;
}

unsigned int PushDoubleRegisterToStack::getTiming(){
    return 16;
}

void PushDoubleRegisterToStack::setParameters(const Memory&, unsigned short){
}

std::string PushDoubleRegisterToStack::toString(){
    return "PUSH " + Registers::getDoubleRegisterName(this->doubleRegName);
}