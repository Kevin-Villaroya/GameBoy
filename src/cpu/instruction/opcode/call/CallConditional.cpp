#include "CallConditional.h"
#include "../../util/DecToHex.h"

CallConditional::CallConditional(Condition condition) : condition(condition){}

void CallConditional::execute(Memory& ram, Registers& registers) {

	if( this->condition(ram, registers) ){
		unsigned short sp = registers.getSP();
		unsigned short pc = registers.getPC();
		
		ram.writeMemory(sp - 1, pc >> 8);
		ram.writeMemory(sp - 2, pc);
		
		registers.setSP(sp-2);
		registers.setPC(this->address); 
		this->timing = 24;
	}
	else this->timing = 12;
}

unsigned int CallConditional::getSize() {
	return 3;
}

unsigned int CallConditional::getTiming() {
	return this->timing;
}

void CallConditional::setParameters(Memory& memory, unsigned short pc) {
	this->address = memory.getDouble(pc);
}

std::string CallConditional::toString(){
    return "CALL " + InstructionCondition::getConditionName(this->condition) + "," + shortToHex(this->address);
}