#include "SubCarryDoubleRegisterToA.h"

SubCarryDoubleRegisterToA::SubCarryDoubleRegisterToA(DoubleRegisterName d):doubleRegName(d){}

void SubCarryDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getDoubleRegister(this->doubleRegName);
    unsigned char aValue = registers.getA()+(registers.isFlagC()?1:0);

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

unsigned int SubCarryDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int SubCarryDoubleRegisterToA::getTiming(){
    return 8;
}

void SubCarryDoubleRegisterToA::setParameters(const Memory&, unsigned short v){
}