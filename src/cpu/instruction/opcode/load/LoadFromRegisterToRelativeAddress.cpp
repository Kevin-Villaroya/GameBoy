#include "LoadFromRegisterToRelativeAddress.h"

LoadFromRegisterToRelativeAddress::LoadFromRegisterToRelativeAddress(RegisterName dest, RegisterName src) : dest(dest), src(src){
    
}

void LoadFromRegisterToRelativeAddress::execute(Memory& ram, Registers& registers){
    unsigned char value = registers.getRegister(this->src);

    unsigned short address = 0xFF00 + registers.getRegister(this->dest);
    ram.set(address, value);
}

unsigned int LoadFromRegisterToRelativeAddress::getSize(){
    return 1;
}

unsigned int LoadFromRegisterToRelativeAddress::getTiming(){
    return 8;
}

void LoadFromRegisterToRelativeAddress::setParameters(const Memory&, unsigned short){

}

std::string LoadFromRegisterToRelativeAddress::toString(){
    return "LD " + Registers::getRegisterName(this->dest) + ", " + Registers::getRegisterName(this->src);
}