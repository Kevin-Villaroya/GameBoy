#include <iostream>
#include "LoadARegisterToHlIncrement.h"

void LoadARegisterToHlIncrement::execute(Memory& ram, Registers& registers){
    unsigned short hlValue = registers.getHL();

    ram.set(hlValue, registers.getA());
    registers.setHL(hlValue + 1);
}

unsigned int LoadARegisterToHlIncrement::getSize(){
    return 1;
}

unsigned int LoadARegisterToHlIncrement::getTiming(){
    return 8;
}

void LoadARegisterToHlIncrement::setParameters(const Memory&, unsigned short){

}