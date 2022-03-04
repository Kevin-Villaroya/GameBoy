#include "AddCarryImmediateToA.h"

AddCarryImmediateToA::AddCarryImmediateToA(){}

void AddCarryImmediateToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
    this->parameter += (registers.isFlagC()?1:0);

    if(this->parameter+aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue&(1<<4))==16) != (((aValue+this->parameter)&(1<<4))==0))
        registers.setFlagH(1);
    else if(((this->parameter&(1<<4))==16) != (((aValue+this->parameter)&(1<<4))==0))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (aValue+this->parameter))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);

    registers.setFlagN(0);
}

unsigned int AddCarryImmediateToA::getSize(){
    return 2;
}

unsigned int AddCarryImmediateToA::getTiming(){
    return 8;
}

void AddCarryImmediateToA::setParameters(const Memory&, unsigned short v){
    this->parameter = v;
}