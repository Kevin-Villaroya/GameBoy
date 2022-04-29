#include "JumpUnconditionalRelativeImmediate.h"

void JumpUnconditionalRelativeImmediate::execute(Memory& ram, Registers& registers){
    registers.setPC(registers.getPC() + this->parameter);
}

unsigned int JumpUnconditionalRelativeImmediate::getSize(){
    return 2;
}

unsigned int JumpUnconditionalRelativeImmediate::getTiming(){
    return 12;
}

void JumpUnconditionalRelativeImmediate::setParameters(const Memory& rom, unsigned short parameterBegin){
    this->parameter = rom[parameterBegin];
}

std::string JumpUnconditionalRelativeImmediate::toString(){
    return "JR " + std::to_string((signed int)this->parameter);
}