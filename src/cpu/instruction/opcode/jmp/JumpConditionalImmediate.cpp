#include "JumpConditionalImmediate.h"

JumpConditionalImmediate::JumpConditionalImmediate(std::function<bool(const Memory&, const Registers&)> test) : test(test) {}

void JumpConditionalImmediate::execute(Memory& ram, Registers& registers){
	if(this->test(ram, registers))
	{
		registers.setPC(this->address);	
	}
}

unsigned int JumpConditionalImmediate::getSize(){
    return 3;
}

unsigned int JumpConditionalImmediate::getTiming(){
    return 12;
}

void JumpConditionalImmediate::setParameters(const Memory& memory, unsigned short pc){
	this->address = memory[pc];
}
