#include <iostream>
#include "LoadHlImmediateSp.h"

void LoadHlImmediateSp::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned short nVal = registers.getSP() + this->value;

    registers.setFlagZ(0);
    registers.setFlagN(0);
    if((registers.getSP()&0xF) + (value & 0xF) >= 0x10){
        registers.setFlagH(1);
    }
    else{
        registers.setFlagH(0);
    }
    if((registers.getSP()&0xFF) + (value & 0xFF) >= 0x100){
        registers.setFlagC(1);
    }
    else{
        registers.setFlagC(0);
    }
    registers.setHL(nVal);
}

unsigned int LoadHlImmediateSp::getSize(){
    return 2;
}

unsigned int LoadHlImmediateSp::getTiming(){
    return 8;
}

void LoadHlImmediateSp::setParameters(const Memory& memory, unsigned short val){
    this->value = (char)memory.get(val);
}

std::string LoadHlImmediateSp::toString(){
    return "LD HL, SP + " ;
}