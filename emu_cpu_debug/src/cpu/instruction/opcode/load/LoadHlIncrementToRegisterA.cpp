#include <iostream>
#include "LoadHlIncrementToRegisterA.h"

void LoadHlIncrementToRegisterA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char hlAdressValue = ram.get(hlValue);

    registers.setA(hlAdressValue);
    registers.setHL(hlValue + 1);
}

unsigned int LoadHlIncrementToRegisterA::getSize(){
    return 1;
}

unsigned int LoadHlIncrementToRegisterA::getTiming(){
    return 8;
}

void LoadHlIncrementToRegisterA::setParameters(const Memory&, unsigned short){

}

std::string LoadHlIncrementToRegisterA::toString(){
    return "LD A, (HL+)";
}