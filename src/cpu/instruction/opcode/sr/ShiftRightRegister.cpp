#include "ShiftRightRegister.h"

ShiftRightRegister::ShiftRightRegister(RegisterName r):registerName(r){}

void ShiftRightRegister::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getRegister(this->registerName);
	bool lastBit = aValue & 0b10000000;

	registers.setFlagC(0b1 & aValue);
	aValue = (aValue>>1) + (lastBit<<7) ;
    aValue == 0 ? registers.setFlagZ(1) : registers.setFlagZ(0);
    registers.setFlagH(0);
    registers.setFlagN(0);
    registers.setRegister(registerName, aValue);
}

unsigned int ShiftRightRegister::getSize(){
    return 2;
}

unsigned int ShiftRightRegister::getTiming(){
    return 8;
}

void ShiftRightRegister::setParameters(Memory&, unsigned short v){
}

std::string ShiftRightRegister::toString(){
    return "SRA " + Registers::getRegisterName(this->registerName);
}