#include "AddCarryHLToA.h"

AddCarryHLToA::AddCarryHLToA(){}

void AddCarryHLToA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char addValue = ram.get(hlValue);
    int carry = (registers.isFlagC() ? 1 : 0);
    unsigned char aValue = registers.getA();

    if((unsigned char)(addValue+aValue+carry) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue & 0b00001111) + (addValue & 0b00001111) + carry) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if((aValue+addValue+carry) > 0xFF)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(0);
    
    registers.setA(addValue + aValue + carry);
}

unsigned int AddCarryHLToA::getSize(){
    return 1;
}

unsigned int AddCarryHLToA::getTiming(){
    return 8;
}

void AddCarryHLToA::setParameters(const Memory&, unsigned short v){
}

std::string AddCarryHLToA::toString(){
    return "ACR A, (HL)";
}