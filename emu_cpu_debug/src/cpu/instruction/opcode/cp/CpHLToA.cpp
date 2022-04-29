#include "CpHLToA.h"
#include "../util/DecToHex.h"
#include <iostream>

CpHLToA::CpHLToA(){}

void CpHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toCpValue = ram.get(hlValue);
    unsigned char aVal = registers.getRegister(RegisterName::A);

    if(toCpValue == aVal)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(1);
    
    if((aVal & 0b00001111) < (toCpValue & 0b00001111))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aVal < toCpValue)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
}

unsigned int CpHLToA::getSize(){
    return 1;
}

unsigned int CpHLToA::getTiming(){
    return 8;
}

void CpHLToA::setParameters(const Memory&, unsigned short){
}

std::string CpHLToA::toString(){
    return "CP (HL)";
}