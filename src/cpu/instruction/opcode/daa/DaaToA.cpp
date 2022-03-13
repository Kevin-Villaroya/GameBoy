#include "DaaToA.h"

DaaToA::DaaToA(){}

void DaaToA::execute(Memory& ram, Registers& registers){
    unsigned char aValue = registers.getA();

    if((aValue&0b00001111 > 9) || (registers.isFlagH())){
        aValue += 6;
    }
    if(((aValue>>4)>9) || (registers.isFlagC())){
        if(aValue+0b01100000 < aValue)
            registers.setFlagC(1);
        else    
            registers.setFlagC(0);
        aValue = aValue+0b01100000;
    }

    if(aValue == 0)
        registers.setFlagZ(1);
    else    
        registers.setFlagZ(0);
    registers.setFlagH(0);

    registers.setA(aValue);
}

unsigned int DaaToA::getSize(){
    return 1;
}

unsigned int DaaToA::getTiming(){
    return 4;
}

void DaaToA::setParameters(const Memory&, unsigned short v){
}
