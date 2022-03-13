#include "SetCarryFlag.h"

SetCarryFlag::SetCarryFlag(){}

void SetCarryFlag::execute(Memory& ram, Registers& registers){
    registers.setFlagH(0);
    registers.setFlagN(0);
    registers.setFlagC(1);
}

unsigned int SetCarryFlag::getSize(){
    return 1;
}

unsigned int SetCarryFlag::getTiming(){
    return 4;
}

void SetCarryFlag::setParameters(const Memory&, unsigned short v){
}
