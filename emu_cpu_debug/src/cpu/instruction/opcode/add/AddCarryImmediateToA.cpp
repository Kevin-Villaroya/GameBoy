#include "AddCarryImmediateToA.h"

AddCarryImmediateToA::AddCarryImmediateToA(){}

void AddCarryImmediateToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    int carry = (registers.isFlagC() ? 1 : 0);

    if((unsigned char)(this->parameter+aValue+carry) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue & 0xF) + (this->parameter & 0xF) + carry) > 0xF)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if((aValue+this->parameter+carry) > 0xFF)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);

    registers.setFlagN(0);
    
    registers.setA(aValue + this->parameter + carry);
}

unsigned int AddCarryImmediateToA::getSize(){
    return 2;
}

unsigned int AddCarryImmediateToA::getTiming(){
    return 8;
}

void AddCarryImmediateToA::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string AddCarryImmediateToA::toString(){
    return "ACR A," + (int)parameter;
}