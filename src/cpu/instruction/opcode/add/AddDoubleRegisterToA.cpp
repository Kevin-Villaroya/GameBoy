#include "AddDoubleRegisterToA.h"

AddDoubleRegisterToA::AddDoubleRegisterToA(DoubleRegisterName d):doubleRegName(d){}

void AddDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getDoubleRegister(this->doubleRegName);
    unsigned char aValue = registers.getA();

    if(regValue+aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue&0b00001111)+(regValue&0b00001111)) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (aValue+regValue))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(0);
}

unsigned int AddDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int AddDoubleRegisterToA::getTiming(){
    return 8;
}

void AddDoubleRegisterToA::setParameters(const Memory&, unsigned short v){
}