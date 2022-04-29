#include "SetBitHL.h"

SetBitHL::SetBitHL(int b):bit(b){}

void SetBitHL::execute(Memory& ram, Registers& registers){
    unsigned short hlVal = registers.getHL();
    unsigned char val = ram.get(hlVal);
    unsigned char compare = 0b1<<this->bit;
    val &= compare;
    
    ram.writeMemory(hlVal, val);
}

unsigned int SetBitHL::getSize(){
    return 2;
}

unsigned int SetBitHL::getTiming(){
    return 16;
}

void SetBitHL::setParameters(const Memory&, unsigned short v){
}

std::string SetBitHL::toString(){
    return "SET " + std::to_string(this->bit) +", ("+ Registers::getDoubleRegisterName(DoubleRegisterName::HL)+")";
}