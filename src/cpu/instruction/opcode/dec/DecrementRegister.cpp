#include "DecrementRegister.h"

DecrementRegister::DecrementRegister(RegisterName registerName) : registerName(registerName){}

void DecrementRegister::execute(Memory& ram, Registers& registers){
    bool byte3Before = registers.getRegister(this->registerName) & 0b00001000;

    unsigned char value = registers.getRegister(this->registerName) - 1;

    bool byte3After = value & 0b00001000;

    registers.setRegister(this->registerName, value);

    if(byte3Before && !byte3After){
        registers.setH(1);
    }else{
        registers.setH(0);
    }

    if(value == 0){
        registers.setFlagZ(1);
    }else{
        registers.setFlagZ(0);
    }

    registers.setFlagN(true);

}

unsigned int DecrementRegister::getSize(){
    return 1;
}

unsigned int DecrementRegister::getTiming(){
    return 4;
}

void DecrementRegister::setParameters(const Memory&, unsigned short){

}