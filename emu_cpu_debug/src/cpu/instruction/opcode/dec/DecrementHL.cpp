#include "DecrementHL.h"

void DecrementHL::execute(Memory& ram, Registers& registers){
	unsigned short valueAddress = registers.getDoubleRegister(DoubleRegisterName::HL);
	
    unsigned char oldValue = ram[valueAddress];
    unsigned char value = ram[valueAddress] - 1;

    ram.writeMemory(valueAddress, value);

    if(oldValue>>4 != value>>3){
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

std::string DecrementHL::toString(){
    return "DEC (HL)";
}