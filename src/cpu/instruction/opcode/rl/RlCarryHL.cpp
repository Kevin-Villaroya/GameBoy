#include "RlCarryHL.h"

RlCarryHL::RlCarryHL(){}

void RlCarryHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char memValue = ram.get(hlValue);
    unsigned char valueOf7bit = memValue>>7;
    memValue <<= 1;
    memValue += valueOf7bit;

    if(memValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf7bit);
    ram.writeMemory(hlValue, memValue);
}

unsigned int RlCarryHL::getSize(){
    return 2;
}

unsigned int RlCarryHL::getTiming(){
    return 16;
}

void RlCarryHL::setParameters(Memory&, unsigned short v){
}

std::string RlCarryHL::toString(){
    return "RLC (HL)";
}