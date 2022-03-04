#include "AddRegisterToA.h"

AddRegisterToA::AddRegisterToA(RegisterName registerName) : registerName(registerName){}

void AddRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char aValue = registers.getA();

    if(regValue+aValue == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue&(1<<4))==16) != (((aValue+regValue)&(1<<4))==0))
        registers.setFlagH(1);
    else if(((regValue&(1<<4))==16) != (((aValue+regValue)&(1<<4))==0))
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if(aValue > (aValue+regValue))
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
}

unsigned int AddRegisterToA::getSize(){
    return 1;
}

unsigned int AddRegisterToA::getTiming(){
    return 4;
}

void AddRegisterToA::setParameters(const Memory&, unsigned short){

}