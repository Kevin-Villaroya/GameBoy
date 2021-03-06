#include "LoadARegisterToHlDecrement.h"

void LoadARegisterToHlDecrement::execute(Memory& ram, Registers& registers){
    
    unsigned short hlValue = registers.getHL();

    ram.writeMemory(hlValue, registers.getA());
    registers.setHL(hlValue - 1);
}

unsigned int LoadARegisterToHlDecrement::getSize(){
    return 1;
}

unsigned int LoadARegisterToHlDecrement::getTiming(){
    return 8;
}

void LoadARegisterToHlDecrement::setParameters(Memory&, unsigned short){

}

std::string LoadARegisterToHlDecrement::toString(){
    return "LD (HL-), A";
}