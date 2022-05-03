#include "BitHl.h"

BitHl::BitHl(unsigned char bit) : bit(bit){}

void BitHl::execute(Memory& ram, Registers& registers){
    unsigned char valueRegister = ram.get(registers.getHL());

    registers.setFlagZ(!(valueRegister & (1<<this->bit)));
    registers.setFlagN(0);
    registers.setFlagH(1);
}

unsigned int BitHl::getSize(){
    return 2;
}

unsigned int BitHl::getTiming(){
    return 12;
}

void BitHl::setParameters(Memory&, unsigned short){

}

std::string BitHl::toString(){
    return "BIT " + std::to_string(((int)this->bit)) + ",(HL)";
}