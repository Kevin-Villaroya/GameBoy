#include "LoadSpToImmediateAddress.h"
#include "../../util/DecToHex.h"

void LoadSpToImmediateAddress::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();

    unsigned char upper = (spValue >> 8);
    unsigned char lower = (spValue & 0xff);

    ram.writeMemory(this->address, lower);
    ram.writeMemory(this->address + 1, upper);
}

unsigned int LoadSpToImmediateAddress::getSize(){
    return 3;
}

unsigned int LoadSpToImmediateAddress::getTiming(){
    return 20;
}

void LoadSpToImmediateAddress::setParameters(Memory& ram, unsigned short pc){
    this->address = ram.getDouble(pc);
}

std::string LoadSpToImmediateAddress::toString(){
    return "LD " + shortToHex(address) + ", SP";
}