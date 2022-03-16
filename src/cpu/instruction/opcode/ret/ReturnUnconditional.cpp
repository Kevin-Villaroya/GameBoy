#include "ReturnUnconditional.h"

void ReturnUnconditional::execute(Memory& ram, Registers& registers) {
	unsigned short sp = registers.getSP();
	
	unsigned short returnAddress = ram[sp + 1];
	returnAddress <<= 8;
	returnAddress += ram[sp];
	
	registers.setPC(returnAddress);
	registers.setSP(sp + 2);
}

unsigned int ReturnUnconditional::getSize() {
	return 1;
}

unsigned int ReturnUnconditional::getTiming() {
	return 8;
}

void ReturnUnconditional::setParameters(const Memory& memory, unsigned short pc) {
}
