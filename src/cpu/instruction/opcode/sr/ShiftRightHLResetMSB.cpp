#include "ShiftRightHLResetMSB.h"

ShiftRightHLResetMSB::ShiftRightHLResetMSB(){}

void ShiftRightHLResetMSB::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getDoubleRegister(DoubleRegisterName::HL);
    unsigned char aValue = ram.get(hlValue);
	bool lastBit = aValue & 0b10000000;

	registers.setFlagC(0b1 & aValue);
	aValue >>= 1;
    aValue == 0 ? registers.setFlagZ(0) : registers.setFlagZ(1);
    registers.setFlagH(0);
    registers.setFlagN(0);
    ram.writeMemory(hlValue, aValue);
}

unsigned int ShiftRightHLResetMSB::getSize(){
    return 2;
}

unsigned int ShiftRightHLResetMSB::getTiming(){
    return 16;
}

void ShiftRightHLResetMSB::setParameters(const Memory&, unsigned short v){
}

std::string ShiftRightHLResetMSB::toString(){
    return "SRL (" + Registers::getDoubleRegisterName(DoubleRegisterName::HL) +")";
}