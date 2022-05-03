#include "DaaToA.h"

/**
 * Check the BCD format validity after standard binary operation (ADD, SUB, ...)
 */
DaaToA::DaaToA(){}

void DaaToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();
	
	unsigned char correction = 0;
	bool flagC = false;
	
	if(registers.isFlagH() || (!registers.isFlagN() && (aValue & 0b1111) > 9)) {
		correction = 0b00000110;
	}
	
	if(registers.isFlagC() || (!registers.isFlagN() && aValue > 0b10011001)) {
		correction |= 0b01100000;
		flagC = true;
	}
	
	if(registers.isFlagN()) {
		aValue -= correction;
	}
	else {
		aValue += correction;
	}
	
	if(aValue == 0) {
		registers.setFlagZ(true);
	}
	else {
		registers.setFlagZ(false);
	}
	
	registers.setFlagC(flagC);
	registers.setFlagH(false);
	
	registers.setA(aValue);
}

unsigned int DaaToA::getSize(){
    return 1;
}

unsigned int DaaToA::getTiming(){
    return 4;
}

void DaaToA::setParameters(Memory&, unsigned short v){
}

std::string DaaToA::toString(){
    return "DAA";
}