#include "RlCarryA.h"

RlCarryA::RlCarryA(){}

void RlCarryA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
	bool lastBit = aValue & 0b10000000;
	
	aValue <<= 1;
	
	if(lastBit) {
		aValue |= 0b00000001;
		registers.setFlagC(true);
	}
	else {
		aValue &= 0b11111110;
		registers.setFlagC(false);
	}
	
	if(aValue == 0) {
		registers.setFlagZ(true);
	}
	else {
		registers.setFlagZ(false);
	}
	
    registers.setFlagH(0);
    registers.setFlagN(0);
    
    registers.setA(aValue);
}

unsigned int RlCarryA::getSize(){
    return 1;
}

unsigned int RlCarryA::getTiming(){
    return 4;
}

void RlCarryA::setParameters(const Memory&, unsigned short v){
}

std::string RlCarryA::toString(){
    return "RLCA";
}