#include "DI.h"
#include "../../../Processor.h"

DI::DI(void* context):cpuContext(context){}

void DI::execute(Memory& ram, Registers& registers){
    ((Processor*)(this->cpuContext))->setEnableIME(false);
    this->cpuContext = NULL;
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