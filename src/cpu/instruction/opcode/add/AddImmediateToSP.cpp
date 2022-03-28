#include "AddImmediateToSP.h"

AddImmediateToSP::AddImmediateToSP(){}

void AddImmediateToSP::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();

    registers.setFlagZ(0);
    registers.setFlagN(0);
    
    if(this->parameter < 0){
        if(((spValue & 0b11111111) < (this->parameter & 0b11111111)))
            registers.setFlagH(1);
        else
            registers.setFlagH(0);
            
        if(spValue < this->parameter)
            registers.setFlagC(1);
        else
            registers.setFlagC(0);
    }
    else{
        if(((spValue & 0b11111111) + (this->parameter & 0b11111111)) > 0b11111111)
            registers.setFlagH(1);
        else
            registers.setFlagH(0);

        if(spValue > (spValue + this->parameter))
            registers.setFlagC(1);
        else
            registers.setFlagC(0);
    }

    registers.setSP(spValue + this->parameter);
}

unsigned int AddImmediateToSP::getSize(){
    return 2;
}

unsigned int AddImmediateToSP::getTiming(){
    return 16;
}

void AddImmediateToSP::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string AddImmediateToSP::toString(){
    return "ADD SP, " + (int)this->parameter;
}