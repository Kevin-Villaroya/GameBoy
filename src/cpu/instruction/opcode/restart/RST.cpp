#include "RST.h"
#include "../../util/DecToHex.h"

RST::RST(unsigned char address) : address(address){}

void RST::execute(Memory& ram, Registers& registers){
    unsigned short spValue = registers.getSP();
    unsigned short pcValue = registers.getPC();

    unsigned char leftRegVal = pcValue >> 8;
    unsigned char rightRegVal = pcValue;
    
    ram.set(spValue-1, leftRegVal);
    ram.set(spValue-2, rightRegVal);
    registers.setSP(spValue-2);

    registers.setPC(this->address);
}

unsigned int RST::getSize(){
    return 1;
}

unsigned int RST::getTiming(){
    return 16;
}

void RST::setParameters(const Memory&, unsigned short){
}

std::string RST::toString(){
    return "RST " + charToHex(this->address);
}