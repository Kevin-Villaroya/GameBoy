#include "OrHLToA.h"

OrHLToA::OrHLToA(){}

void OrHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toOrValue = ram.get(hlValue);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(toOrValue | aVal);

    if((toOrValue | aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagC(0);
    registers.setFlagH(0);
}

unsigned int OrHLToA::getSize(){
    return 1;
}

unsigned int OrHLToA::getTiming(){
    return 8;
}

void OrHLToA::setParameters(const Memory&, unsigned short){
}
