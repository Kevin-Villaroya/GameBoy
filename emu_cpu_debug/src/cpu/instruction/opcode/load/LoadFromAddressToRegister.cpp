#include "LoadFromAddressToRegister.h"

LoadFromAddressToRegister::LoadFromAddressToRegister(RegisterName dest, DoubleRegisterName src) : dest(dest), src(src) {}

void LoadFromAddressToRegister::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getDoubleRegister(this->src);
	unsigned char value = ram[valueAddress];
	
	registers.setRegister(this->dest, value);
}

unsigned int LoadFromAddressToRegister::getSize() {
	return 1;
}

unsigned int LoadFromAddressToRegister::getTiming() {
	return 8;
}

void LoadFromAddressToRegister::setParameters(Memory&, unsigned short) {}

std::string LoadFromAddressToRegister::toString(){
    return "LD " + Registers::getRegisterName(this->dest) + ", " + Registers::getDoubleRegisterName(this->src);
}