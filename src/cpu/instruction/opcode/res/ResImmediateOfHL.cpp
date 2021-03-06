#include "ResImmediateOfHL.h"
#include "../../util/DecToHex.h"
#include <math.h>

ResImmediateOfHL::ResImmediateOfHL(unsigned char bit) : bit(bit){}

void ResImmediateOfHL::execute(Memory& ram, Registers& registers){
    unsigned short valueHL = registers.getHL();
    unsigned char valueHlAdress = ram.get(valueHL);

    valueHlAdress &= 0xFF - (unsigned char)pow(2, bit);

    ram.set(valueHL, valueHlAdress);
}

unsigned int ResImmediateOfHL::getSize(){
    return 2;
}

unsigned int ResImmediateOfHL::getTiming(){
    return 16;
}

void ResImmediateOfHL::setParameters(Memory&, unsigned short){
}

std::string ResImmediateOfHL::toString(){
    return "RES " + std::to_string((int)this->bit) + ", (HL)";
}