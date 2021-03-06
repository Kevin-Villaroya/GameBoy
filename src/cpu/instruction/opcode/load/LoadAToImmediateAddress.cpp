#include "LoadAToImmediateAddress.h"
#include "../../util/DecToHex.h"

void LoadAToImmediateAddress::execute(Memory& ram, Registers& registers) {
	unsigned short absoluteAddress = 0xFF00 + this->address;
	unsigned char aValue = registers.getA();

	if(absoluteAddress == 0xFF05){
		printf("ok\n");
	}
	ram.writeMemory(absoluteAddress, aValue);
}

unsigned int LoadAToImmediateAddress::getSize() {
	return 2;
}

unsigned int LoadAToImmediateAddress::getTiming() {
	return 12;
}

void LoadAToImmediateAddress::setParameters(Memory& memory, unsigned short pc) {
	this->address = memory[pc];
}

std::string LoadAToImmediateAddress::toString(){
    return "LD " + charToHex(address) + ", A";
}