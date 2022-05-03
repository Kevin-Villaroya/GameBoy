#include "LoadImmediateToRegister.h"
#include "../../util/DecToHex.h"

LoadImmediateToRegister::LoadImmediateToRegister(RegisterName registerName){
    this->registerName = registerName;
}
        
void LoadImmediateToRegister::execute(Memory& ram, Registers& registers){
    registers.setRegister(this->registerName, this->parameter);
}

unsigned int LoadImmediateToRegister::getSize(){
    return 2;
}

unsigned int LoadImmediateToRegister::getTiming(){
    return 8;
}

void LoadImmediateToRegister::setParameters(Memory& memory, unsigned short positionParameters){
    this->parameter = memory.get(positionParameters);
}

std::string LoadImmediateToRegister::toString(){
    return "LD " + Registers::getRegisterName(this->registerName) + ", " + charToHex(this->parameter);
}