#include "LoadHLToRegister.h"

LoadHLToRegister::LoadHLToRegister(RegisterName dest) : dest(dest) {}

void LoadHLToRegister::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getHL();
	unsigned char value = ram[valueAddress];
	
	registers.setRegister(this->dest, value);
}

unsigned int LoadHLToRegister::getSize() {
	return 1;
}

unsigned int LoadHLToRegister::getTiming() {
	return 8;
}

void LoadHLToRegister::setParameters(const Memory&, unsigned short) {}
