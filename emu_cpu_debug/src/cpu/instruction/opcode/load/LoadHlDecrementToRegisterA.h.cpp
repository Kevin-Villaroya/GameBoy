#include <iostream>
#include "LoadHlDecrementToRegisterA.h"

void LoadHlDecrementToRegisterA::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();
    unsigned char hlAdressValue = ram.get(hlValue);

    registers.setA(hlAdressValue);
    registers.setHL(hlValue - 1);
}

unsigned int LoadHlDecrementToRegisterA::getSize(){
    return 1;
}

unsigned int LoadHlDecrementToRegisterA::getTiming(){
    return 8;
}

void LoadHlDecrementToRegisterA::setParameters(Memory&, unsigned short){

}

std::string LoadHlDecrementToRegisterA::toString(){
    return "LD A,(HL-)";
}