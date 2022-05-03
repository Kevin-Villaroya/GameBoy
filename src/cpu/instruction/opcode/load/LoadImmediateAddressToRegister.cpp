#include "LoadImmediateAddressToRegister.h"
#include "../../util/DecToHex.h"

LoadImmediateAddressToRegister::LoadImmediateAddressToRegister(RegisterName registerName) : registerName(registerName){}

void LoadImmediateAddressToRegister::execute(Memory& ram, Registers& registers){
    unsigned char value = ram.get(this->address);

    registers.setRegister(this->registerName, value);
}

unsigned int LoadImmediateAddressToRegister::getSize(){
    return 3;
}

unsigned int LoadImmediateAddressToRegister::getTiming(){
    return 16;
}

void LoadImmediateAddressToRegister::setParameters(Memory& ram, unsigned short pc){
    this->address = ram.getDouble(pc);
}

std::string LoadImmediateAddressToRegister::toString(){
    return "LD " + Registers::getRegisterName(this->registerName) + ", (" + shortToHex(this->address) + ")";
}