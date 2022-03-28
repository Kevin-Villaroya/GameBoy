
#include "DI.h"

void DI::execute(Memory& ram, Registers& registers){
    registers.disableIME();
}

unsigned int DI::getSize(){
    return 1;
}

unsigned int DI::getTiming(){
    return 4;
}

void DI::setParameters(const Memory&, unsigned short){

}

std::string DI::toString(){
    return "DI";
}