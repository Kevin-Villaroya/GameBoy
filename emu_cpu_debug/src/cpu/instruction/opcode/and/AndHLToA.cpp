#include "AndHLToA.h"

AndHLToA::AndHLToA(){}

void AndHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toAndValue = ram.get(hlValue);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(toAndValue & aVal);

    if((toAndValue & aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagH(1);
    registers.setFlagC(0);
}

unsigned int AndHLToA::getSize(){
    return 1;
}

unsigned int AndHLToA::getTiming(){
    return 8;
}

void AndHLToA::setParameters(const Memory&, unsigned short){
}

std::string AndHLToA::toString(){
    return "AND (HL)";
}