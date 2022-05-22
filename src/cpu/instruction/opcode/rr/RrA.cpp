#include "RrA.h"

RrA::RrA(){}

void RrA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
	bool firstBit = aValue & 0b00000001;
	
	aValue >>= 1;
	
	if(registers.isFlagC()) {
		aValue |= 0b10000000;
	}
	else {
		aValue &= 0b01111111;
	}
	
	if(firstBit) {
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

unsigned int RrA::getSize(){
    return 1;
}

unsigned int RrA::getTiming(){
    return 4;
}

void RrA::setParameters(Memory&, unsigned short v){
}

std::string RrA::toString(){
    return "RRA";
}