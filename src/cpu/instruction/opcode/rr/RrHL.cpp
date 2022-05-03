#include "RrHL.h"

RrHL::RrHL(){}

void RrHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char memValue = ram.get(hlValue);
    unsigned char valueOf0bit = memValue&0b00000001;
    memValue >>= 1;
    memValue += ((unsigned char)(registers.isFlagC()?1:0))<<7;
    if(memValue == 0)
        registers.setFlagZ(1);
    else   
        registers.setFlagZ(0);
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(valueOf0bit);
    ram.writeMemory(hlValue, memValue);
}

unsigned int RrHL::getSize(){
    return 2;
}

unsigned int RrHL::getTiming(){
    return 16;
}

void RrHL::setParameters(Memory&, unsigned short v){
}

std::string RrHL::toString(){
    return "RR (HL)";
}