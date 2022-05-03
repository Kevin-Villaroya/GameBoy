#include "EI.h"
#include "../../../Processor.h"

EI::EI(void* c):context(c){}

void EI::execute(Memory& ram, Registers& registers){
    ((Processor*)(this->context))->setIME(true);
    this->context = NULL;
}

unsigned int EI::getSize(){
    return 1;
}

unsigned int EI::getTiming(){
    return 4;
}

void EI::setParameters(Memory&, unsigned short){

}

std::string EI::toString(){
    return "EI";
}