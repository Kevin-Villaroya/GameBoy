#include "ReturnConditional.h"

ReturnConditional::ReturnConditional(Condition condition) : condition(condition){}

void ReturnConditional::execute(Memory& ram, Registers& registers){
	if(this->condition(ram, registers)){
		unsigned short sp = registers.getSP();
		unsigned short pc;
		
		pc = ram[sp + 1];
		pc <<= 8;
		pc += ram[sp];
		
		registers.setSP(sp + 2);
		registers.setPC(pc);
	}
}

unsigned int ReturnConditional::getSize(){
	return 1;
}

unsigned int ReturnConditional::getTiming(){
 return 16;
}

void ReturnConditional::setParameters(const Memory&, unsigned short){}

std::string ReturnConditional::toString(){
    return "RET" + InstructionCondition::getConditionName(this->condition);
}