#include "AddImmediateToA.h"
#include "../../util/DecToHex.h"

AddImmediateToA::AddImmediateToA(){}

void AddImmediateToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();

    if((unsigned char)(this->parameter + aValue) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue & 0b00001111) + (this->parameter & 0b00001111)) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (unsigned char)(aValue + this->parameter))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);

    registers.setFlagN(0);
    
    registers.setA(aValue + this->parameter);
}

unsigned int AddImmediateToA::getSize(){
    return 2;
}

unsigned int AddImmediateToA::getTiming(){
    return 8;
}

void AddImmediateToA::setParameters(Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string AddImmediateToA::toString(){
    return "ADD A, " + charToHex(this->parameter);
}