#include "XorHLToA.h"

XorHLToA::XorHLToA(){}

void XorHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toXorValue = ram.get(hlValue);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    registers.setA(toXorValue&aVal);

    if(toXorValue^aVal == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
    registers.setFlagN(1);
    registers.setFlagC(0);
    registers.setFlagH(1);
}

unsigned int XorHLToA::getSize(){
    return 1;
}

unsigned int XorHLToA::getTiming(){
    return 8;
}

void XorHLToA::setParameters(const Memory&, unsigned short){
}