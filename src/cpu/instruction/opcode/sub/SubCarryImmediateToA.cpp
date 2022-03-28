#include "SubCarryImmediateToA.h"
#include "../../util/DecToHex.h"

SubCarryImmediateToA::SubCarryImmediateToA(){}

void SubCarryImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aValue = registers.getA();
    this->parameter += registers.isFlagC() ? 1 : 0;

    if(this->parameter-aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (this->parameter & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < this->parameter)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - this->parameter);
}

unsigned int SubCarryImmediateToA::getSize(){
    return 2;
}

unsigned int SubCarryImmediateToA::getTiming(){
    return 8;
}

void SubCarryImmediateToA::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string SubCarryImmediateToA::toString(){
    return "SBC A, " + charToHex(this->parameter);
}