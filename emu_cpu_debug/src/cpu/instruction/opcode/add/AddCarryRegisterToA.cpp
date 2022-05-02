#include "AddCarryRegisterToA.h"

AddCarryRegisterToA::AddCarryRegisterToA(RegisterName r) : registerName(r){}

void AddCarryRegisterToA::execute(Memory& ram, Registers& registers){
    unsigned char regCarryValue = registers.getRegister(registerName);
    int carry =  (registers.isFlagC() ? 1 : 0);
    unsigned char aValue = registers.getA();

    if((unsigned char)(regCarryValue + aValue + carry) == 0)
        registers.setFlagZ(1);
    else
        registers.setFlagZ(0);
    
    if(((aValue & 0b00001111) + (regCarryValue & 0b00001111) + carry) > 0b00001111)
        registers.setFlagH(1);
    else
        registers.setFlagH(0);

    if((aValue+regCarryValue+carry) > 0xFF)
        registers.setFlagC(1);
    else
        registers.setFlagC(0);
    
    registers.setFlagN(0);
    
    registers.setA(regCarryValue + aValue + carry);
}

unsigned int AddCarryRegisterToA::getSize(){
    return 1;
}

unsigned int AddCarryRegisterToA::getTiming(){
    return 4;
}

void AddCarryRegisterToA::setParameters(Memory&, unsigned short){

}

std::string AddCarryRegisterToA::toString(){
    return "ACR A," + Registers::getRegisterName(this->registerName);
}