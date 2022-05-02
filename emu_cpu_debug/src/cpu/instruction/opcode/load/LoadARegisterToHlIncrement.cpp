#include <iostream>
#include "LoadARegisterToHlIncrement.h"

void LoadARegisterToHlIncrement::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();

    ram.writeMemory(hlValue, registers.getA());
    registers.setHL(hlValue + 1);
}

unsigned int LoadARegisterToHlIncrement::getSize(){
    return 1;
}

unsigned int LoadARegisterToHlIncrement::getTiming(){
    return 8;
}

void LoadARegisterToHlIncrement::setParameters(Memory&, unsigned short){

}

std::string LoadARegisterToHlIncrement::toString(){
    return "LD (HL+), A";
}