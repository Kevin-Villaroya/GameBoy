#include "LoadRegisterToHL.h"

LoadRegisterToHL::LoadRegisterToHL(RegisterName src) : src(src) {}

void LoadRegisterToHL::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getHL();
	unsigned char value = registers.getRegister(this->src);
	ram[valueAddress] = value;
}

unsigned int LoadRegisterToHL::getSize() {
	return 1;
}

unsigned int LoadRegisterToHL::getTiming() {
	return 8;
}

void LoadRegisterToHL::setParameters(const Memory&, unsigned short) {}
