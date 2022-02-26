#include "Processor.h"
#include "InstructionFactory.h"
#include "startupException/StartupException.h"
#include <iostream>

Processor::Processor(char* path) : memory(path){
}

Instruction* Processor::fetch(){
    this->registers.incrementPc(12);

    unsigned char instrByte = this->memory[this->registers.getPC()];

    Instruction* currentInstr = this->decodeAndLoad(instrByte);
    this->registers.incrementPc(currentInstr->getSize());

    return currentInstr;
}

Instruction* Processor::decodeAndLoad(unsigned char byteInstr){
    Instruction* instr = InstructionFactory::forCode(byteInstr);
    instr->setParameters(this->memory);

    return instr;
}

bool Processor::execute(Instruction& instr){
    return instr.execute();
}

bool Processor::startupSequence(){
    //TODO
    return true;
}

bool Processor::run(){
    bool canBoot = this->startupSequence();

    if(canBoot){
        this->memory.init();
        this->registers.init(this->memory);
        this->registers.setPC(0x100);

        while (true)
        {
            Instruction* instr = this->fetch();
            this->execute(*instr);
            //display
        }
    }else{
        throw startupSequence();
    }  
}