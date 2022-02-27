#include "Processor.h"
#include "InstructionFactory.h"
#include "startupException/StartupException.h"
#include <iostream>

Processor::Processor(char* path) : memory(path){
}

Instruction* Processor::fetch(){
    unsigned char instrByte = this->memory[this->registers.getPC()];

    Instruction* currentInstr = this->decodeAndLoad(instrByte);
    this->registers.incrementPc(currentInstr->getSize());

    return currentInstr;
}

Instruction* Processor::decodeAndLoad(unsigned char byteInstr){
    Instruction* instr = InstructionFactory::forCode(byteInstr);
    instr->setParameters(this->memory, this->registers.getPC() + 1);

    return instr;
}

void Processor::execute(Instruction& instr){
    instr.execute(this->memory, this->registers);
}

bool Processor::startupSequence(){
    //TODO
    return true;
}

void Processor::run(){
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

            delete instr;
        }
    }else{
        throw startupSequence();
    }  
}