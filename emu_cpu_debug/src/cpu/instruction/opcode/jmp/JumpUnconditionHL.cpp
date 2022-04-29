#include <iostream>
#include "JumpUnconditionHL.h"
#include "../../util/DecToHex.h"

void JumpUnconditionHL::execute(Memory& ram, Registers& registers){
    registers.setPC(registers.getDoubleRegister(DoubleRegisterName::HL));
}

unsigned int JumpUnconditionHL::getSize(){
    return 1;
}

unsigned int JumpUnconditionHL::getTiming(){
    return 8;
}

void JumpUnconditionHL::setParameters(const Memory& rom, unsigned short parameterBegin){}

std::string JumpUnconditionHL::toString(){
    return "JP HL";
}