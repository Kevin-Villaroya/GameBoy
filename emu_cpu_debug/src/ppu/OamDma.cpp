#include "OamDma.h"
#include "../memory/Memory.h"

void OamDma::dmaStart(){
    this->active = true;
    this->bytePtr = 0;
    this->delay = 2;
}

void OamDma::dmaTick(void* mem){
    Memory* memory = (Memory*) mem;
    if(this->active){
        if(this->delay){
            this->delay--;
            return;
        }
        unsigned char value = memory->memory[DMA_REGISTER];
        memory->memory[this->offSet + this->bytePtr] = memory->get((value * 100) + this->bytePtr);

        this->bytePtr++;
        this->active = this->bytePtr < 0xA0;
    }

}

bool OamDma::isActive(){
    return this->active;
}