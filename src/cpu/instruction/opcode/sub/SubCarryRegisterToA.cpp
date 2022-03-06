#include "SubCarryRegisterToA.h"

SubCarryRegisterToA::SubCarryRegisterToA(RegisterName r) : registerName(r){}

void SubCarryRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char aValue = registers.getA()+(registers.isFlagC()?1:0);

    if(regValue-aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if((aValue&0b00001111) < (regValue&0b00001111))
        registers.setFlagH(0);
    else
        registers.setFlagH(1);

    if(aValue < regValue)
        registers.setFlagC(0);
    else
        registers.setFlagC(1);
    
    registers.setFlagN(1);
}

unsigned int SubCarryRegisterToA::getSize(){
    return 1;
}

unsigned int SubCarryRegisterToA::getTiming(){
    return 4;
}

void SubCarryRegisterToA::setParameters(const Memory&, unsigned short){

}