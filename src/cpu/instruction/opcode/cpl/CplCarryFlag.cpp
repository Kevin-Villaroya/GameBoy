#include "CplCarryFlag.h"

CplCarryFlag::CplCarryFlag(){}

void CplCarryFlag::execute(Memory& ram, Registers& registers){
    registers.setFlagC(!registers.isFlagC());
    registers.setFlagH(0);
    registers.setFlagN(0);
}

unsigned int CplCarryFlag::getSize(){
    return 1;
}

unsigned int CplCarryFlag::getTiming(){
    return 4;
}

void CplCarryFlag::setParameters(const Memory&, unsigned short v){
}

std::string CplCarryFlag::toString(){
    return "CPL";
}