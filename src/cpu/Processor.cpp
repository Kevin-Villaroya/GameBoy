#include "Processor.h"

Processor::Processor(uint8_t rom[CARTRIGBE_SIZE]){
    for(int i = 0; i < CARTRIGBE_SIZE; i++){
        this->rom[i] = rom[i];
    }
}

Instruction* Processor::fetch(){
    unsigned char instrByte = this->rom[this->registers.getPC()];

    Instruction* currentInstr = this->decode(instrByte);
    this->registers.incrementPc(currentInstr->getSize());

    return currentInstr;
}

Instruction* Processor::decode(unsigned char instr){
    
}

bool Processor::execute(Instruction& instr){
    return instr.execute();
}

bool Processor::run(){
    while (true)
    {
        Instruction* instr = this->fetch();
        this->execute(*instr);
    }
}