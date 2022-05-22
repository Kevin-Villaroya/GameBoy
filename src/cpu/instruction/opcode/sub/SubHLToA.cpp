#include "SubHLToA.h"

SubHLToA::SubHLToA(){}

void SubHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toSubValue = ram.get(hlValue);
    unsigned char aValue = registers.getA();

    if(aValue - toSubValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (toSubValue & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < toSubValue)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - toSubValue);
}

unsigned int SubHLToA::getSize(){
    return 1;
}

unsigned int SubHLToA::getTiming(){
    return 8;
}

void SubHLToA::setParameters(Memory&, unsigned short v){
}

std::string SubHLToA::toString(){
    return "SUB (HL)";
}