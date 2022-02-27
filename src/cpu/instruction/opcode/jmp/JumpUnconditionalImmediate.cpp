#include <iostream>
#include "JumpUnconditionalImmediate.h"

void JumpUnconditionalImmediate::execute(Memory& ram, Registers& registers){
    registers.setPC(this->parameter);
}

unsigned int JumpUnconditionalImmediate::getSize(){
    return 3;
}

unsigned int JumpUnconditionalImmediate::getTiming(){
    return 16;
}

void JumpUnconditionalImmediate::setParameters(const Memory& rom, unsigned short parameterBegin){
    this->parameter = rom.getDouble(parameterBegin);
}