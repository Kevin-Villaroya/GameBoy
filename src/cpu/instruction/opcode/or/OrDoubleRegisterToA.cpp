#include "OrDoubleRegisterToA.h"

OrDoubleRegisterToA::OrDoubleRegisterToA(DoubleRegisterName r):doubleRegisterName(r){}

void OrDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getDoubleRegister(doubleRegisterName);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(regVal&aVal);

    if(regVal|aVal == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    registers.setFlagC(0);
    registers.setFlagH(1);
}

unsigned int OrDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int OrDoubleRegisterToA::getTiming(){
    return 8;
}

void OrDoubleRegisterToA::setParameters(const Memory&, unsigned short){
}