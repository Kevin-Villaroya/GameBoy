#include <fstream>
#include <iostream>
#include "Memory.h"

Memory::Memory(char* path){
    this->timerCounter = 1024;
    this->dividerCounter = 0;

    this->resetMemory();

    std::ifstream romFile;
    romFile.open(path, std::ifstream::in);

    int current = 0;

    while (romFile.good()) {
        char character = romFile.get();
        if(!romFile.eof()){
            if(current <= CARTRIGBE_SIZE) {
                this->memory[current] = character;        
                current++;
            }
            else {
                std::cerr << "Trying to load more data than a standard cartridge rom" << std::endl;
                break;
            }
        }
    }

    romFile.close();
}

void Memory::init(){  
    this->setBootMemory();
    this->setMemory();
}

unsigned char Memory::get(unsigned short pos) const{

    if(this->hasReadBootRom() && pos <= 256){
        return this->bootRom[pos];
    }else{
        return this->memory[pos];
    }
}

void Memory::set(unsigned short pos, unsigned char value){
    this->memory[pos] = value;    
}

void Memory::writeMemory(unsigned short pos, unsigned char value){
    if(pos == Memory::DIVIDER){

        memory[Memory::DIVIDER] = 0;
    }else if (Memory::TMC == pos){

        unsigned char currentfreq = this->getClockFrequency();
        this->memory[pos] = value;
        unsigned char newfreq = this->getClockFrequency();

        if (currentfreq != newfreq){
            this->setClockFrequency();
        }
    }else{
        this->memory[pos] = value;
    }
    
}

unsigned char Memory::operator[](unsigned short pos)const {
    return this->get(pos);
}

void Memory::resetMemory(){
    for(int i = 0; i < RAM_SIZE; i++){
        this->memory[i] = 0;
    }

    for(int i = 0x0104; i < 0x0104 + 52; i++){
        this->memory[i] = 255;
    }
}

unsigned short Memory::getDouble(unsigned short pos) const{
    unsigned short value;
    
    value = this->get(pos + 1);
    value = value << 8;
    value = value | this->get(pos);

    return value;
}

int Memory::getTimerCounter(){
    return this->timerCounter;
}

unsigned char* Memory::getBootRom(){
    return this->bootRom;
}

bool Memory::hasReadBootRom() const{
    return this->memory[0xFF50] == 0;
}

void Memory::updateTimers(int cycles){
    this->doDividerRegister(cycles);

    if(this->isClockEnabled()){
        this->timerCounter -= cycles;

        if(this->timerCounter <= 0){
            this->setClockFrequency();

            if(this->get(Memory::TIMA) == 255){
                this->writeMemory(Memory::TIMA, 0);
                //this->requestInterupt(2);TODO
            }else{
                this->writeMemory(Memory::TIMA, this->get(Memory::TIMA) + 1);
            }
        }
    }
}

void Memory::setBootMemory(){

    std::ifstream romFile;
    romFile.open("assets/bin/boot_rom.bin", std::ifstream::in);

    int current = 0;

    while (romFile.good()) {
        char character = romFile.get();
        if(!romFile.eof()){
            this->bootRom[current] = character;        
            current++;
        }
    }

    romFile.close();
}

void Memory::setMemory(){
    this->memory[0xFF05] = 0; //TIMA
    this->memory[0xFF06] = 0; //TMA
    this->memory[0xFF07] = 0; //TAC
    this->memory[0xFF10] = this->memory[0x80]; //NR10
    this->memory[0xFF11] = this->memory[0xBF]; //NR11
    this->memory[0xFF12] = this->memory[0xF3]; //NR12
    this->memory[0xFF14] = this->memory[0xBF]; //NR14
    this->memory[0xFF16] = this->memory[0x3F]; //NR21
    this->memory[0xFF17] = 0; //NR22
    this->memory[0xFF19] = this->memory[0xBF]; //NR24
    this->memory[0xFF1A] = this->memory[0x7F]; //NR30
    this->memory[0xFF1B] = this->memory[0xFF]; //NR31
    this->memory[0xFF1C] = this->memory[0x9F]; //NR32
    this->memory[0xFF1E] = this->memory[0xBF]; //NR33
    this->memory[0xFF20] = this->memory[0xFF]; //NR41
    this->memory[0xFF21] = 0; //NR42
    this->memory[0xFF22] = 0; //NR43
    this->memory[0xFF23] = this->memory[0xBF]; //NR30
    this->memory[0xFF24] = this->memory[0x77]; //NR50
    this->memory[0xFF25] = this->memory[0xF3]; //NR51
    this->memory[0xFF26] = this->memory[0xF1]; //NR52
    this->memory[0xFF40] = this->memory[0x91]; //LDC
    this->memory[0xFF42] = 0; //SCY
    this->memory[0xFF43] = 0; //SCX
    this->memory[0xFF45] = 0; //LYC
    this->memory[0xFF47] = this->memory[0xFC]; //BGP
    this->memory[0xFF48] = this->memory[0xFF]; //OBP0
    this->memory[0xFF49] = this->memory[0xFF]; //OBP1
    this->memory[0xFF4A] = 0; //WY
    this->memory[0xFF4B] = 0; //WX
    this->memory[0xFFFF] = 0; //IE
}

bool Memory::isClockEnabled(){
    return (this->get(Memory::TMC) & 0b00000100) != 0;
}

unsigned char Memory::getClockFrequency(){
    return this->get(Memory::TMC) & 0x3;
}

void Memory::setClockFrequency(){
    unsigned char frequency = this->getClockFrequency();

    switch (frequency){
    case 0:
        this->timerCounter = 1024;
        break;
    case 1:
        this->timerCounter = 16;
        break;
    case 2:
        this->timerCounter = 64;
        break;
    case 3:
        this->timerCounter = 256;
        break;
    default:
        break;
    }
}

void Memory::doDividerRegister(int cycles){ //every 256 cycles Divider value increments
    this->dividerCounter += cycles;

    if(dividerCounter >= 255){
        dividerCounter = 0;
        this->set(Memory::DIVIDER, this->get(Memory::DIVIDER) + 1);
    }
}