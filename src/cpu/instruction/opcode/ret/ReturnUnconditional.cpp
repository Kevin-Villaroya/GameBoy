#include "ReturnUnconditional.h"

void ReturnUnconditional::execute(Memory& ram, Registers& registers){
	unsigned short sp = registers.getSP();
	unsigned short pc;
	
	pc = ram[sp + 1];
	pc <<= 8;
	pc += ram[sp];
	
	registers.setSP(sp + 2);
	registers.setPC(pc);
}

unsigned int ReturnUnconditional::getSize(){
	return 1;
}

unsigned int ReturnUnconditional::getTiming(){
 return 16;
}

void ReturnUnconditional::setParameters(const Memory&, unsigned short){}
