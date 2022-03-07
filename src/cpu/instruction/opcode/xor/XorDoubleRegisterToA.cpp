#include "XorDoubleRegisterToA.h"

XorDoubleRegisterToA::XorDoubleRegisterToA(DoubleRegisterName r):doubleRegisterName(r){}

void XorDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getDoubleRegister(doubleRegisterName);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(regVal&aVal);

    if(regVal^aVal == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    registers.setFlagC(0);
    registers.setFlagH(1);
}

unsigned int XorDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int XorDoubleRegisterToA::getTiming(){
    return 8;
}

void XorDoubleRegisterToA::setParameters(const Memory&, unsigned short){
}