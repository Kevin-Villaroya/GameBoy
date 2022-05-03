#include "XorImmediateToA.h"
#include "../../util/DecToHex.h"

XorImmediateToA::XorImmediateToA(){}

void XorImmediateToA::execute(Memory& ram, Registers& registers){;
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(this->parameter ^ aVal);

    if((this->parameter ^ aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagC(0);
    registers.setFlagH(0);
}

unsigned int XorImmediateToA::getSize(){
    return 2;
}

unsigned int XorImmediateToA::getTiming(){
    return 8;
}

void XorImmediateToA::setParameters(Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string XorImmediateToA::toString(){
    return "XOR " + charToHex(this->parameter);
}