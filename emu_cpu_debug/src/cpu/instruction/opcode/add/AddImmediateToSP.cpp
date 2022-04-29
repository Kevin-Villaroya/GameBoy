#include "AddImmediateToSP.h"
#include "../../util/DecToHex.h"

AddImmediateToSP::AddImmediateToSP(){}

void AddImmediateToSP::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();

    registers.setFlagZ(0);
    registers.setFlagN(0);

    
    if((spValue & 0xF) + ((unsigned char)this->parameter & 0xF) >= 0x10)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if((spValue & 0xFF) + ((unsigned char)this->parameter & 0xFF) >= 0x100)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);


    registers.setSP(spValue + this->parameter);
}

unsigned int AddImmediateToSP::getSize(){
    return 2;
}

unsigned int AddImmediateToSP::getTiming(){
    return 12;
}

void AddImmediateToSP::setParameters(const Memory& memory, unsigned short pc){
    this->parameter = memory[pc];
}

std::string AddImmediateToSP::toString(){
    return "ADD SP, " + charToHex(this->parameter);
}