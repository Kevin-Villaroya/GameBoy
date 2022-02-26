#include <fstream>
#include <iostream>
#include "Memory.h"

Memory::Memory(char* path){
    std::ifstream romFile;
    romFile.open(path, std::ifstream::in);

    int current = 0;

    unsigned short beginName = 0x134;
    unsigned short lastName = 0x142;

    std::string name;

    while (romFile.good()) {
        char character = romFile.get();

        this->memory[current] = character;


        if(current >= beginName && current <= lastName){
            name += character;
        }
        
        current++;
    }

    std::cout << "the game " << name << " has been successfully loaded" << std::endl;

    romFile.close();
}

void Memory::init(){
    this->resetMemory();
    this->setMemory();
}

unsigned char Memory::get(unsigned short pos){
    return this->memory[pos];
}

unsigned char Memory::operator[](unsigned short pos){
    return this->memory[pos];
}

void Memory::resetMemory(){
    unsigned char value = this->memory[0x00];

    for(int i = 0; i < RAM_SIZE; i++){
        this->memory[i] = value;
    }
}

void Memory::setMemory(){
    this->memory[0xFF05] = this->memory[0x00]; //TIMA
    this->memory[0xFF06] = this->memory[0x00]; //TMA
    this->memory[0xFF07] = this->memory[0x00]; //TAC
    this->memory[0xFF10] = this->memory[0x80]; //NR10
    this->memory[0xFF11] = this->memory[0xBF]; //NR11
    this->memory[0xFF12] = this->memory[0xF3]; //NR12
    this->memory[0xFF14] = this->memory[0xBF]; //NR14
    this->memory[0xFF16] = this->memory[0x3F]; //NR21
    this->memory[0xFF17] = this->memory[0x00]; //NR22
    this->memory[0xFF19] = this->memory[0xBF]; //NR24
    this->memory[0xFF1A] = this->memory[0x7F]; //NR30
    this->memory[0xFF1B] = this->memory[0xFF]; //NR31
    this->memory[0xFF1C] = this->memory[0x9F]; //NR32
    this->memory[0xFF1E] = this->memory[0xBF]; //NR33
    this->memory[0xFF20] = this->memory[0xFF]; //NR41
    this->memory[0xFF21] = this->memory[0x00]; //NR42
    this->memory[0xFF22] = this->memory[0x00]; //NR43
    this->memory[0xFF23] = this->memory[0xBF]; //NR30
    this->memory[0xFF24] = this->memory[0x77]; //NR50
    this->memory[0xFF25] = this->memory[0xF3]; //NR51
    this->memory[0xFF26] = this->memory[0xF1]; //NR52
    this->memory[0xFF40] = this->memory[0x91]; //LDC
    this->memory[0xFF42] = this->memory[0x00]; //SCY
    this->memory[0xFF43] = this->memory[0x00]; //SCX
    this->memory[0xFF45] = this->memory[0x00]; //LYC
    this->memory[0xFF47] = this->memory[0xFC]; //BGP
    this->memory[0xFF48] = this->memory[0xFF]; //OBP0
    this->memory[0xFF49] = this->memory[0xFF]; //OBP1
    this->memory[0xFF4A] = this->memory[0x00]; //WY
    this->memory[0xFF4B] = this->memory[0x00]; //WX
    this->memory[0xFFFF] = this->memory[0x00]; //IE
}