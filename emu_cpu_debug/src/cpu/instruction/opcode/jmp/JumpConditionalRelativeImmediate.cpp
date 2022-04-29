#include "JumpConditionalRelativeImmediate.h"

JumpConditionalRelativeImmediate::JumpConditionalRelativeImmediate(Condition condition) : condition(condition){}

void JumpConditionalRelativeImmediate::execute(Memory& ram, Registers& registers){
    if(this->condition(ram, registers)){
        registers.setPC(registers.getPC() + this->address);
        this->timing = 12;
    }
    else{
        this->timing = 8;
    }
}

unsigned int JumpConditionalRelativeImmediate::getSize(){
    return 2;
}

unsigned int JumpConditionalRelativeImmediate::getTiming(){
    return this->timing;
}

void JumpConditionalRelativeImmediate::setParameters(const Memory& ram, unsigned short pc){
    this->address = ram.get(pc);
}

std::string JumpConditionalRelativeImmediate::toString(){
    return "JR " + InstructionCondition::getConditionName(this->condition) + ", " + std::to_string((int)this->address);
}