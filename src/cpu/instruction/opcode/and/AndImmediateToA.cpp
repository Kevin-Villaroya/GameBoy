#include "AndImmediateToA.h"
#include "../../util/DecToHex.h"

AndImmediateToA::AndImmediateToA(){}

void AndImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(this->parameter & aVal);

    if((this->parameter & aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagH(1);
    registers.setFlagC(0);
}

unsigned int AndImmediateToA::getSize(){
    return 2;
}

unsigned int AndImmediateToA::getTiming(){
    return 8;
}

void AndImmediateToA::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string AndImmediateToA::toString(){
    return "AND " + charToHex(this->parameter);
}