#include "EI.h"

void EI::execute(Memory& ram, Registers& registers){
    registers.enableIME();
}

unsigned int EI::getSize(){
    return 1;
}

unsigned int EI::getTiming(){
    return 4;
}

void EI::setParameters(const Memory&, unsigned short){

}

std::string EI::toString(){
    return "EI";
}