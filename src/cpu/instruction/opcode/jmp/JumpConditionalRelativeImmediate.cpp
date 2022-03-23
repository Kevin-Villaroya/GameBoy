#include "JumpConditionalRelativeImmediate.h"

JumpConditionalRelativeImmediate::JumpConditionalRelativeImmediate(Condition condition) : condition(condition){}

void JumpConditionalRelativeImmediate::execute(Memory& ram, Registers& registers){
    if(this->condition(ram, registers)){
        registers.setPC(registers.getPC() + this->address);
    }
}

unsigned int JumpConditionalRelativeImmediate::getSize(){
    return 2;
}

unsigned int JumpConditionalRelativeImmediate::getTiming(){
    return 6;
}

void JumpConditionalRelativeImmediate::setParameters(const Memory& ram, unsigned short pc){
    this->address = ram.get(pc);
}