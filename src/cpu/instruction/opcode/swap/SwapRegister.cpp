#include "SwapRegister.h"

SwapRegister::SwapRegister(RegisterName r):registerName(r){}

void SwapRegister::execute(Memory& ram, Registers& registers){
    unsigned char regValue = registers.getRegister(registerName);
    unsigned char nRegValue = (regValue >> 4) + (regValue << 4);

    if(nRegValue == 0)
        registers.setFlagZ(1);
    else    
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagH(0);
    registers.setFlagC(0);

    registers.setRegister(registerName, nRegValue);
}

unsigned int SwapRegister::getSize(){
    return 2;
}

unsigned int SwapRegister::getTiming(){
    return 8;
}

void SwapRegister::setParameters(Memory&, unsigned short v){
}

std::string SwapRegister::toString(){
    return "SWAP " + Registers::getRegisterName(this->registerName);
}