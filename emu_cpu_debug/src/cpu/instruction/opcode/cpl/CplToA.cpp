#include "CplToA.h"

CplToA::CplToA(){}

void CplToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();

    aValue = aValue ^ 0b11111111;

    registers.setFlagN(1);
    registers.setFlagH(1);

    registers.setA(aValue);
}

unsigned int CplToA::getSize(){
    return 1;
}

unsigned int CplToA::getTiming(){
    return 4;
}

void CplToA::setParameters(Memory&, unsigned short v){
}

std::string CplToA::toString(){
    return "CCF";
}