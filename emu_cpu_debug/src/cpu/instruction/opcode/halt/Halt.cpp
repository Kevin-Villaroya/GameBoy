#include "Halt.h"
#include "../../../Processor.h"

Halt::Halt(void* c):context(c){}

void Halt::execute(Memory& ram, Registers& registers){
    ((Processor*)(this->context))->setHalt(true);
    this->context = NULL;
}

unsigned int Halt::getSize(){
    return 1;
}

unsigned int Halt::getTiming(){
    return 4;
}

void Halt::setParameters(const Memory&, unsigned short){

}

std::string Halt::toString(){
    return "HALT";
}