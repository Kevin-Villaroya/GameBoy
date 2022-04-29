#include "SwapHL.h"

SwapHL::SwapHL(){}

void SwapHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char memValue = ram.get(hlValue);
    unsigned char nMemValue = (memValue >> 4) + (memValue << 4);

    if(nMemValue == 0)
        registers.setFlagZ(1);
    else    
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(0);

    ram.writeMemory(hlValue, nMemValue);
}

unsigned int SwapHL::getSize(){
    return 2;
}

unsigned int SwapHL::getTiming(){
    return 16;
}

void SwapHL::setParameters(const Memory&, unsigned short v){
}

std::string SwapHL::toString(){
    return "SWAP (HL)";
}