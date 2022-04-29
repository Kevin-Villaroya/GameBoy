#include "LoadRegisterToImmediateAddress.h"
#include "../../util/DecToHex.h"

LoadRegisterToImmediateAddress::LoadRegisterToImmediateAddress(RegisterName registerName) : registerName(registerName){}

void LoadRegisterToImmediateAddress::execute(Memory& ram, Registers& registers){
    unsigned char value = registers.getRegister(this->registerName);

    ram.writeMemory(this->address, value);
}

unsigned int LoadRegisterToImmediateAddress::getSize(){
    return 3;
}

unsigned int LoadRegisterToImmediateAddress::getTiming(){
    return 16;
}

void LoadRegisterToImmediateAddress::setParameters(const Memory& ram, unsigned short pc){
    this->address = ram.getDouble(pc);
}

std::string LoadRegisterToImmediateAddress::toString(){
    return "LD (" + shortToHex(this->address) + "), " + Registers::getRegisterName(this->registerName);
}