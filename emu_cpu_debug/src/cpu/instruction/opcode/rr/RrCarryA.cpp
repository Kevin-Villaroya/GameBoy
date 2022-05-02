#include "RrCarryA.h"

RrCarryA::RrCarryA(){}

void RrCarryA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
	bool firstBit = aValue & 0b00000001;
	
	aValue >>= 1;
	
	if(firstBit) {
		aValue |= 0b10000000;
		registers.setFlagC(true);
	}
	else {
		aValue &= 0b01111111;
		registers.setFlagC(false);
	}
	
	registers.setFlagZ(false);	
    registers.setFlagH(0);
    registers.setFlagN(0);
    
    registers.setA(aValue);
}

unsigned int RrCarryA::getSize(){
    return 1;
}

unsigned int RrCarryA::getTiming(){
    return 4;
}

void RrCarryA::setParameters(Memory&, unsigned short v){
}

std::string RrCarryA::toString(){
    return "RRCA";
}