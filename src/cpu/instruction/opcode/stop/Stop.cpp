#include "Stop.h"

void Stop::execute(Memory& ram, Registers& registers){
    
}

unsigned int Stop::getSize(){
    return 2;
}

unsigned int Stop::getTiming(){
    return 4;
}

void Stop::setParameters(Memory&, unsigned short v){
}

std::string Stop::toString(){
    return "STOP";
}
