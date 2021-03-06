#include "LoadFromRegisterToRelativeAddress.h"

LoadFromRegisterToRelativeAddress::LoadFromRegisterToRelativeAddress(RegisterName dest, RegisterName src) : dest(dest), src(src){
    
}

void LoadFromRegisterToRelativeAddress::execute(Memory& ram, Registers& registers){
    unsigned char value = registers.getRegister(this->src);

    unsigned short address = 0xFF00 + registers.getRegister(this->dest);
    ram.writeMemory(address, value);
}

unsigned int LoadFromRegisterToRelativeAddress::getSize(){
    return 1;
}

unsigned int LoadFromRegisterToRelativeAddress::getTiming(){
    return 8;
}

void LoadFromRegisterToRelativeAddress::setParameters(Memory&, unsigned short){

}

std::string LoadFromRegisterToRelativeAddress::toString(){
    return "LD (FF00" + Registers::getRegisterName(this->dest) + "), " + Registers::getRegisterName(this->src);
}