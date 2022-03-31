#include "IncrementHL.h"
#include <iostream>

void IncrementHL::execute(Memory& ram, Registers& registers){
	unsigned short valueAddress = registers.getDoubleRegister(DoubleRegisterName::HL);
	
    bool byte3Before = ram[valueAddress] & 0b00001000;
    unsigned char value = ram.get(valueAddress) + 1;
    bool byte3After = value & 0b00001000;

    ram.set(valueAddress, value);

    if(byte3Before && !byte3After){
        registers.setFlagH(1);
    }else{
        registers.setFlagH(0);
    }

    if(value == 0){
        registers.setFlagZ(1);
    }else{
        registers.setFlagZ(0);
    }

    registers.setFlagN(0);

}

unsigned int IncrementHL::getSize(){
    return 1;
}

unsigned int IncrementHL::getTiming(){
    return 12;
}

void IncrementHL::setParameters(const Memory&, unsigned short){

}

std::string IncrementHL::toString(){
    return "INC (HL)";
}