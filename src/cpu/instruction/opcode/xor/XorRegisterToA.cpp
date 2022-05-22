#include "XorRegisterToA.h"

XorRegisterToA::XorRegisterToA(RegisterName r):registerName(r){}

void XorRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regVal = registers.getRegister(registerName);
    unsigned char aVal = registers.getRegister(RegisterName::A);
    
    registers.setA(regVal ^ aVal);

    if((regVal ^ aVal) == 0)
        registers.setFlagZ(1);
    else 
        registers.setFlagZ(0);
        
    registers.setFlagN(0);
    registers.setFlagC(0);
    registers.setFlagH(0);
}

unsigned int XorRegisterToA::getSize(){
    return 1;
}

unsigned int XorRegisterToA::getTiming(){
    return 4;
}

void XorRegisterToA::setParameters(Memory&, unsigned short){
}

std::string XorRegisterToA::toString(){
    return "XOR " + Registers::getRegisterName(this->registerName);
}