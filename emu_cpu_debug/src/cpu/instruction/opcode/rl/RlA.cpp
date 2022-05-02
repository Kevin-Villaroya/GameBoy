#include "RlA.h"

RlA::RlA(){}

void RlA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
	bool lastBit = aValue & 0b10000000;
	
	aValue <<= 1;
	
	if(registers.isFlagC()) {
		aValue |= 0b00000001;
	}
	else {
		aValue &= 0b11111110;
	}
	
	if(lastBit) {
		registers.setFlagC(true);
	}
	else {
		registers.setFlagC(false);
	}
	

	registers.setFlagZ(false);

	
    registers.setFlagH(0);
    registers.setFlagN(0);
    
    registers.setA(aValue);
}

unsigned int RlA::getSize(){
    return 1;
}

unsigned int RlA::getTiming(){
    return 4;
}

void RlA::setParameters(Memory&, unsigned short v){
}

std::string RlA::toString(){
    return "RLA";
}