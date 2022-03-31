#include "LoadRegisterToAddressFromImmediate.h"
#include "../util/DecToHex.h"

LoadRegisterToAddressFromImmediate::LoadRegisterToAddressFromImmediate(DoubleRegisterName addr) : addr(addr){}

void LoadRegisterToAddressFromImmediate::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getDoubleRegister(this->addr);

	ram.set(valueAddress, this->parameter);
}

unsigned int LoadRegisterToAddressFromImmediate::getSize() {
	return 1;
}

unsigned int LoadRegisterToAddressFromImmediate::getTiming() {
	return 8;
}

void LoadRegisterToAddressFromImmediate::setParameters(const Memory& ram, unsigned short pc) {
    this->parameter = ram.get(pc);
}

std::string LoadRegisterToAddressFromImmediate::toString(){
    return "LD (" + Registers::getDoubleRegisterName(this->addr) + "), " + charToHex(this->parameter);
}