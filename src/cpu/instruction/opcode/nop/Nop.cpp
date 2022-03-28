#include "Nop.h"

void Nop::execute(Memory& ram, Registers& registers){

}

unsigned int Nop::getSize(){
    return 1;
}

unsigned int Nop::getTiming(){
    return 4;
}

void Nop::setParameters(const Memory&, unsigned short){

}

std::string Nop::toString(){
    return "NOP";
}