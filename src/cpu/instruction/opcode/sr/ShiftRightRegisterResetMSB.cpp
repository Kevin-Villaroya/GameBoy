#include "ShiftRightRegisterResetMSB.h"

ShiftRightRegisterResetMSB::ShiftRightRegisterResetMSB(RegisterName r):registerName(r){}

void ShiftRightRegisterResetMSB::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getRegister(this->registerName);
	bool lastBit = aValue & 0b10000000;

	registers.setFlagC(0b1 & aValue);
	aValue >>= 1;
    aValue == 0 ? registers.setFlagZ(0) : registers.setFlagZ(1);
    registers.setFlagH(0);
    registers.setFlagN(0);
    registers.setRegister(registerName, aValue);
}

unsigned int ShiftRightRegisterResetMSB::getSize(){
    return 2;
}

unsigned int ShiftRightRegisterResetMSB::getTiming(){
    return 8;
}

void ShiftRightRegisterResetMSB::setParameters(const Memory&, unsigned short v){
}

std::string ShiftRightRegisterResetMSB::toString(){
    return "SRL " + Registers::getRegisterName(this->registerName);
}