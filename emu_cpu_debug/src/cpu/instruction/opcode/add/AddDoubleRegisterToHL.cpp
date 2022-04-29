#include "AddDoubleRegisterToHL.h"

AddDoubleRegisterToHL::AddDoubleRegisterToHL(DoubleRegisterName d):doubleRegName(d){}

void AddDoubleRegisterToHL::execute(Memory& ram, Registers& registers){
    unsigned short regValue = registers.getDoubleRegister(this->doubleRegName);
    unsigned short aValue = registers.getHL();
    
    if(((aValue & 0xFFF) + (regValue & 0xFFF)) >= 0x1000){
        registers.setFlagH(1);}
    else
        registers.setFlagH(0);

    if(aValue > (unsigned short)(aValue + regValue))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(0);
    
    registers.setHL((unsigned short)(regValue + aValue));
}

unsigned int AddDoubleRegisterToHL::getSize(){
    return 1;
}

unsigned int AddDoubleRegisterToHL::getTiming(){
    return 8;
}

void AddDoubleRegisterToHL::setParameters(const Memory&, unsigned short v){
}

std::string AddDoubleRegisterToHL::toString(){
    return "ADD HL," + Registers::getDoubleRegisterName(this->doubleRegName);
}