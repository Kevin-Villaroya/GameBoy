#include "LoadRegisterToAddressFromRegister.h"

LoadRegisterToAddressFromRegister::LoadRegisterToAddressFromRegister(DoubleRegisterName addr, RegisterName src) : addr(addr), src(src) {}

void LoadRegisterToAddressFromRegister::execute(Memory& ram, Registers& registers) {
	unsigned short valueAddress = registers.getDoubleRegister(this->addr);
	unsigned char value = registers.getRegister(this->src);
	ram[valueAddress] = value;
}

unsigned int LoadRegisterToAddressFromRegister::getSize() {
	return 1;
}

unsigned int LoadRegisterToAddressFromRegister::getTiming() {
	return 8;
}

void LoadRegisterToAddressFromRegister::setParameters(const Memory&, unsigned short) {}

std::string LoadRegisterToAddressFromRegister::toString(){
    return "LD (" + Registers::getDoubleRegisterName(this->addr) + "), " + Registers::getRegisterName(this->src);
}