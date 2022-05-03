#include "SubCarryRegisterToA.h"

SubCarryRegisterToA::SubCarryRegisterToA(RegisterName r) : registerName(r){}

void SubCarryRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    int carry = (registers.isFlagC() ? 1 : 0);
    unsigned char aValue = registers.getA();

    if((unsigned char)(regValue-aValue+carry) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (regValue & 0b00001111) + carry)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < regValue + carry)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - regValue - carry);
}

unsigned int SubCarryRegisterToA::getSize(){
    return 1;
}

unsigned int SubCarryRegisterToA::getTiming(){
    return 4;
}

void SubCarryRegisterToA::setParameters(Memory&, unsigned short){

}

std::string SubCarryRegisterToA::toString(){
    return "SBC A, " + Registers::getRegisterName(this->registerName);
}