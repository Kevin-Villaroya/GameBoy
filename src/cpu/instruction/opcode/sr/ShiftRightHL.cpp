#include "ShiftRightHL.h"

ShiftRightHL::ShiftRightHL(){}

void ShiftRightHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char aValue = ram.get(hlValue);
	bool lastBit = aValue & 0b10000000;
	
	registers.setFlagC(0b1 & aValue);
	aValue = (aValue>>1) + lastBit ;
    aValue == 0 ? registers.setFlagZ(0) : registers.setFlagZ(1);
    registers.setFlagH(0);
    registers.setFlagN(0);
    ram.set(hlValue, aValue);
}

unsigned int ShiftRightHL::getSize(){
    return 2;
}

unsigned int ShiftRightHL::getTiming(){
    return 16;
}

void ShiftRightHL::setParameters(const Memory&, unsigned short v){
}

std::string ShiftRightHL::toString(){
    return "SRA (" + Registers::getDoubleRegisterName(DoubleRegisterName::HL) +")";
}
