#include "LoadFromImmediateRelativeAddressToRegister.h"

LoadFromImmediateRelativeAddressToRegister::LoadFromImmediateRelativeAddressToRegister(RegisterName registerName) : registerName(registerName){}

void LoadFromImmediateRelativeAddressToRegister::execute(Memory& ram, Registers& registers){
    unsigned char value = ram[0xFF00 + this->relativeAddress];

    registers.setRegister(this->registerName, value);
}

unsigned int LoadFromImmediateRelativeAddressToRegister::getSize(){
    return 2;
}

unsigned int LoadFromImmediateRelativeAddressToRegister::getTiming(){
    return 12;
}

void LoadFromImmediateRelativeAddressToRegister::setParameters(const Memory& ram, unsigned short pc){
    this->relativeAddress = ram.get(pc);
}