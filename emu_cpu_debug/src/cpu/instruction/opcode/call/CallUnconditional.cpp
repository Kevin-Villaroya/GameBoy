#include "CallUnconditional.h"
#include "../../util/DecToHex.h"

#include <iostream>

void CallUnconditional::execute(Memory& ram, Registers& registers) {
	unsigned short sp = registers.getSP();
	unsigned short pc = registers.getPC();
	
	ram.writeMemory(sp - 1, pc >> 8);
	ram.writeMemory(sp - 2, pc);
	
	registers.setSP(sp - 2);
	registers.setPC(this->address);
}

unsigned int CallUnconditional::getSize() {
	return 3;
}

unsigned int CallUnconditional::getTiming() {
	return 24;
}

void CallUnconditional::setParameters(const Memory& memory, unsigned short pc) {
	this->address = memory.getDouble(pc);
}

std::string CallUnconditional::toString(){
    return "CALL " + shortToHex(this->address);
}