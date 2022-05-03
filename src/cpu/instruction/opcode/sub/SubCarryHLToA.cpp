#include "SubCarryHLToA.h"

SubCarryHLToA::SubCarryHLToA(){}

void SubCarryHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char toSubValue = ram.get(hlValue);
    int carry =  (registers.isFlagC() ? 1 : 0);
    unsigned char aValue = registers.getA();

    if((unsigned char)(toSubValue-aValue+carry) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue & 0b00001111) < (toSubValue & 0b00001111) + carry)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue < toSubValue+ carry)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(1);
    
    registers.setA(aValue - toSubValue - carry);
}

unsigned int SubCarryHLToA::getSize(){
    return 1;
}

unsigned int SubCarryHLToA::getTiming(){
    return 8;
}

void SubCarryHLToA::setParameters(Memory&, unsigned short v){
}

std::string SubCarryHLToA::toString(){
    return "SBC A, (HL)";
}