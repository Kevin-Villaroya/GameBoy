#include "AddCarryDoubleRegisterToA.h"

AddCarryDoubleRegisterToA::AddCarryDoubleRegisterToA(DoubleRegisterName d):doubleRegName(d){}

void AddCarryDoubleRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regCarryValue = registers.getDoubleRegister(this->doubleRegName)+(registers.isFlagC()?1:0);
    unsigned char aValue = registers.getA();

    if(regCarryValue+aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue&0b00001111)+(regCarryValue&0b00001111)) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (aValue+regCarryValue))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(0);
}

unsigned int AddCarryDoubleRegisterToA::getSize(){
    return 1;
}

unsigned int AddCarryDoubleRegisterToA::getTiming(){
    return 8;
}

void AddCarryDoubleRegisterToA::setParameters(const Memory&, unsigned short v){
}