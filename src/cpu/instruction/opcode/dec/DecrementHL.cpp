#include "DecrementHL.h"

void DecrementHL::execute(Memory& ram, Registers& registers){
	unsigned short valueAddress = registers.getDoubleRegister(DoubleRegisterName::HL);
	
    bool byte3Before = ram[valueAddress] & 0b00001000;
    unsigned char value = ram[valueAddress] - 1;
    bool byte3After = value & 0b00001000;

    ram[valueAddress] = value;

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

    registers.setFlagN(true);

}

unsigned int DecrementHL::getSize(){
    return 1;
}

unsigned int DecrementHL::getTiming(){
    return 12;
}

void DecrementHL::setParameters(const Memory&, unsigned short){

}
