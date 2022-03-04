#include "PushDoubleRegisterToStack.h"

PushDoubleRegisterToStack::PushDoubleRegisterToStack(DoubleRegisterName r):doubleRegName(r){}

void PushDoubleRegisterToStack::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();
    unsigned short doubleRegVal = registers.getDoubleRegister(doubleRegName);
    unsigned char leftRegVal = doubleRegVal >> 8;
    unsigned char rightRegVal = doubleRegVal;
    ram.set(spValue, rightRegVal);
    spValue--;
    ram.set(spValue, leftRegVal);
    spValue--;
    registers.setSP(spValue);
}

unsigned int PushDoubleRegisterToStack::getSize(){
    return 1;
}

unsigned int PushDoubleRegisterToStack::getTiming(){
    return 16;
}

void PushDoubleRegisterToStack::setParameters(const Memory&, unsigned short){
}