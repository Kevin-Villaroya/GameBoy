#include "AddImmediateToSP.h"

AddImmediateToSP::AddImmediateToSP(){}

void AddImmediateToSP::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getSP();

    registers.setFlagZ(0);
    
    if(((aValue&0b00001111)+(this->parameter&0b00001111)) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (aValue+this->parameter))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);

    registers.setFlagN(0);
}

unsigned int AddImmediateToSP::getSize(){
    return 2;
}

unsigned int AddImmediateToSP::getTiming(){
    return 16;
}

void AddImmediateToSP::setParameters(const Memory&, char v){
    this->parameter = v;
}