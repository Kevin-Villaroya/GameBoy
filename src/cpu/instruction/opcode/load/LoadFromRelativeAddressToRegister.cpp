#include "LoadFromRelativeAddressToRegister.h"

LoadFromRelativeAddressToRegister::LoadFromRelativeAddressToRegister(RegisterName dest, RegisterName addressRegister) : dest(dest), addressRegister(addressRegister) {}

void LoadFromRelativeAddressToRegister::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getRegister(this->addressRegister) + 0xFF00;
	unsigned char value = ram[valueAddress];
	
	registers.setRegister(this->dest, value);
}

unsigned int LoadFromRelativeAddressToRegister::getSize() {
	return 1;
}

unsigned int LoadFromRelativeAddressToRegister::getTiming() {
	return 8;
}

void LoadFromRelativeAddressToRegister::setParameters(const Memory&, unsigned short) {}

std::string LoadFromRelativeAddressToRegister::toString(){
    return "LD " + Registers::getRegisterName(this->addressRegister) + ", " + Registers::getRegisterName(this->dest);
}