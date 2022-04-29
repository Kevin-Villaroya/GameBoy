#include "ShiftLeftRegister.h"

ShiftLeftRegister::ShiftLeftRegister(RegisterName r):registerName(r){}

void ShiftLeftRegister::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getRegister(this->registerName);
	bool lastBit = aValue & 0b10000000;
	
	aValue <<= 1;
    aValue == 0 ? registers.setFlagZ(1) : registers.setFlagZ(0);
    registers.setFlagC(lastBit);
    registers.setFlagH(0);
    registers.setFlagN(0);
    registers.setRegister(registerName, aValue);
}

unsigned int ShiftLeftRegister::getSize(){
    return 2;
}

unsigned int ShiftLeftRegister::getTiming(){
    return 8;
}

void ShiftLeftRegister::setParameters(const Memory&, unsigned short v){
}

std::string ShiftLeftRegister::toString(){
    return "SLA " + Registers::getRegisterName(this->registerName);
}