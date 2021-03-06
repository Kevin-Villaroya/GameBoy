#include "ShiftLeftHL.h"

ShiftLeftHL::ShiftLeftHL(){}

void ShiftLeftHL::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char aValue = ram.get(hlValue);
	bool lastBit = aValue & 0b10000000;
	
	aValue <<= 1;
    aValue == 0 ? registers.setFlagZ(1) : registers.setFlagZ(0);
    registers.setFlagC(lastBit);
    registers.setFlagH(0);
    registers.setFlagN(0);
    ram.writeMemory(hlValue, aValue);
}

unsigned int ShiftLeftHL::getSize(){
    return 2;
}

unsigned int ShiftLeftHL::getTiming(){
    return 16;
}

void ShiftLeftHL::setParameters(Memory&, unsigned short v){
}

std::string ShiftLeftHL::toString(){
    return "SLA (" + Registers::getDoubleRegisterName(DoubleRegisterName::HL) +")";
}
