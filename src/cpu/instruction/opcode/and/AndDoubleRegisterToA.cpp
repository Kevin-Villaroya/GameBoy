#include "AndDoubleRegisterToA.h"

AndDoubleRegisterToA::AndDoubleRegisterToA(DoubleRegisterName r):doubleRegisterName(r){}

void AndDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getDoubleRegister(doubleRegisterName);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(regVal&aVal);

    if(regVal&aVal == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    registers.setFlagC(0);
    registers.setFlagH(1);
}

unsigned int AndDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int AndDoubleRegisterToA::getTiming(){
    return 8;
}

void AndDoubleRegisterToA::setParameters(const Memory&, unsigned short){
}