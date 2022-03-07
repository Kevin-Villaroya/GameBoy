#include "SubDoubleRegisterToA.h"

SubDoubleRegisterToA::SubDoubleRegisterToA(DoubleRegisterName d):doubleRegName(d){}

void SubDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getDoubleRegister(this->doubleRegName);
    unsigned char aValue = registers.getA();

    if(regValue-aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue&0b00001111) < (regValue&0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < regValue)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
}

unsigned int SubDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int SubDoubleRegisterToA::getTiming(){
    return 8;
}

void SubDoubleRegisterToA::setParameters(const Memory&, unsigned short v){
}