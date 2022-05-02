#include <iostream>
#include "LoadHlToSp.h"

void LoadHlToSp::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    registers.setSP(hlValue);
}

unsigned int LoadHlToSp::getSize(){
    return 1;
}

unsigned int LoadHlToSp::getTiming(){
    return 4;
}

void LoadHlToSp::setParameters(Memory&, unsigned short){

}

std::string LoadHlToSp::toString(){
    return "LD SP, HL";
}