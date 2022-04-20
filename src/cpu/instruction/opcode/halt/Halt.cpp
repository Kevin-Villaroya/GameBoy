#include "Halt.h"

void Halt::execute(Memory& ram, Registers& registers){
    registers.setHalt();
}

unsigned int Halt::getSize(){
    return 1;
}

unsigned int Halt::getTiming(){
    return 1;
}

void Halt::setParameters(const Memory&, unsigned short){

}

std::string Halt::toString(){
    return "HALT";
}