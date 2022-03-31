#include "CallConditional.h"
#include "../../util/DecToHex.h"

CallConditional::CallConditional(Condition condition) : condition(condition){}

void CallConditional::execute(Memory& ram, Registers& registers) {

	if( this->condition(ram, registers) ){
		unsigned short sp = registers.getSP();
		unsigned short pc = registers.getPC();
		
		ram.set(sp - 1, pc >> 8);
		ram.set(sp - 2, pc);
		
		registers.setSP(sp-2);
		registers.setPC(this->address); 
	}
}

unsigned int CallConditional::getSize() {
	return 3;
}

unsigned int CallConditional::getTiming() {
	return 8;
}

void CallConditional::setParameters(const Memory& memory, unsigned short pc) {
	this->address = memory.getDouble(pc);
}

std::string CallConditional::toString(){
    return "CALL " + InstructionCondition::getConditionName(this->condition) + "," + shortToHex(this->address);
}