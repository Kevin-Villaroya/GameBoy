#include "ReturnInterruptServiceRoutine.h"

void ReturnInterruptServiceRoutine::execute(Memory& ram, Registers& registers){
	unsigned short sp = registers.getSP();
    unsigned short pc;
    
    pc = ram[sp + 1];
    pc <<= 8;
    pc += ram[sp];
    
    registers.setSP(sp + 2);
    registers.setPC(pc);

    registers.enableIME();
}

unsigned int ReturnInterruptServiceRoutine::getSize(){
	return 1;
}

unsigned int ReturnInterruptServiceRoutine::getTiming(){
 return 16;
}

void ReturnInterruptServiceRoutine::setParameters(const Memory&, unsigned short){}

std::string ReturnInterruptServiceRoutine::toString(){
    return "RETI";
}