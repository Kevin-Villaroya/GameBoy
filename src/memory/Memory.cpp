#include <fstream>
#include <iostream>
#include "Memory.h"
#include "../util/BitMath.h"
#include "../util/DecToHex.h"
#include "Gamepad.h"


Memory::Memory(char* path){
    this->timerCounter = 1024;
    this->dividerClock = 0;
    this->dividerCounter = 0;

    this->resetMemory();

    std::ifstream romFile;
    romFile.open(path, std::ifstream::in);

    unsigned short current = 0;
    while (romFile.good()) {
        unsigned char character = romFile.get();
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

    std::cout<<"Cartridge loaded"<<std::endl;
    this->printCartridgeHeader(this->memory);

    romFile.close();
}

void Memory::init(OamDma* o){ 
    this->oamDma = o; 
    this->setBootMemory();
    this->setMemory();
}


unsigned char Memory::get(unsigned short pos){
    if(pos >= 0xFE00 && pos < 0xFEA0){
            if(this->oamDma->isActive()){
                return 0xFF;
            }
    }else if(pos == Memory::JOYPAD){
        return Gamepad::getInstance()->get();
    }

    return this->memory[pos];
}

void Memory::set(unsigned short pos, unsigned char value){
    if(pos > CARTRIGBE_SIZE){

        if(pos == DIVIDER){
            this->memory[DIVIDER] = 0;
            this->dividerClock = 0;
        }

        if(pos == DMA){
            this->oamDma->dmaStart();
        }

        if(pos == BGP){
            this->updatePalette(value, 0);
        }
        if(pos == BGP + 1){
            updatePalette(value & 0b11111100, 1);
        }
        if(pos == BGP + 2){
            updatePalette(value & 0b11111100, 1);
        }

        if(pos >= 0xFE00 && pos < 0xFEA0){
            if(this->oamDma->isActive()){
                return;
            }
        }

        this->memory[pos] = value;
    }
}

void Memory::incDividerClock(){
    if(this->dividerClock == 0xFF){
        this->dividerClock = 0;
        this->memory[DIVIDER]++;
    }
    else{
        this->dividerClock++;
    }
}

unsigned char Memory::getDividerClock(){
    return this->dividerClock;
}

void Memory::writeMemory(unsigned short pos, unsigned char value){
    if(pos == Memory::DIVIDER){
        this->set(Memory::DIVIDER, 0);

    }else if (Memory::TMC == pos){
        unsigned char currentfreq = this->getClockFrequency();
        this->set(pos, value);
        unsigned char newfreq = this->getClockFrequency();

        if (currentfreq != newfreq){
            this->setClockFrequency();
        }

    }else if (pos == Memory::LY){
        this->set(pos, 0);

    }else if(pos == Memory::DMA){
        this->dmaTransfer(value);
    }else if(pos == Memory::JOYPAD){
        Gamepad::getInstance()->set(value);
    }else{
        this->set(pos, value);
    }
}

unsigned char Memory::operator[](unsigned short pos) {
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

unsigned short Memory::getDouble(unsigned short pos){
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

bool Memory::hasReadBootRom(){
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
                this->requestInterupt(2);
            }else{
                this->writeMemory(Memory::TIMA, this->get(Memory::TIMA) + 1);
            }
        }
    }
}

void Memory::requestInterupt(unsigned char bit){
    unsigned char value = this->get(Memory::IF);
    setBit(value, bit);
    
    this->set(Memory::IF, value);
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
    this->memory[0xFF04] = 0xAC; //DIV
    this->memory[0xFF05] = 0; //TIMA
    this->memory[0xFF06] = 0; //TMA
    this->memory[0xFF07] = 0; //TAC
    this->memory[0xFF0F] = 0; //INTERRUPT FLAGS
    this->memory[0xFF10] = 0x80; //NR10
    this->memory[0xFF11] = 0xBF; //NR11
    this->memory[0xFF12] = 0xF3; //NR12
    this->memory[0xFF14] = 0xBF; //NR14
    this->memory[0xFF16] = 0x3F; //NR21
    this->memory[0xFF17] = 0; //NR22
    this->memory[0xFF19] = 0xBF; //NR24
    this->memory[0xFF1A] = 0x7F; //NR30
    this->memory[0xFF1B] = 0xFF; //NR31
    this->memory[0xFF1C] = 0x9F; //NR32
    this->memory[0xFF1E] = 0xBF; //NR33
    this->memory[0xFF20] = 0xFF; //NR41
    this->memory[0xFF21] = 0; //NR42
    this->memory[0xFF22] = 0; //NR43
    this->memory[0xFF23] = 0xBF; //NR30
    this->memory[0xFF24] = 0x77; //NR50
    this->memory[0xFF25] = 0xF3; //NR51
    this->memory[0xFF26] = 0xF1; //NR52
    this->memory[0xFF40] = 0x91; //LDC
    this->memory[0xFF42] = 0; //SCY
    this->memory[0xFF43] = 0; //SCX
    this->memory[0xFF44] = 0; //LY
    this->memory[0xFF45] = 0; //LYC
    this->memory[0xFF47] = 0xFC; //BGP
    this->memory[0xFF48] = 0xFF; //OBP0
    this->memory[0xFF49] = 0xFF; //OBP1
    this->memory[0xFF4A] = 0; //WY
    this->memory[0xFF4B] = 0; //WX
    this->memory[0xFFFF] = 0; //IE

    for (int i=0 ; i<4 ; i++) {
        this->bgpColors[i] = defaultColors[i];
        this->sp1Colors[i] = defaultColors[i];
        this->sp2Colors[i] = defaultColors[i];
    }
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

void Memory::dmaTransfer(unsigned char value){
    unsigned short address = value << 8;
    for (int i = 0 ; i < 0xA0; i++){
        this->writeMemory(0xFE00 + i, this->get(address + i));
    }
}

void Memory::printCartridgeHeader(unsigned char* header){    
    char* title = new char[17];
    title = (char *)(header + 0x134);
    title[16] = '\0';
    printf("\t Title    : %s\n", title);

    u_int8_t type = (u_int8_t)header[0x147];
    printf("\t Type     : %2.2X\n", type);

    u_int8_t romSize = (u_int8_t)header[0x148];
    printf("\t ROM size : %d KB\n", 32<<romSize);

    u_int8_t ramSize = (u_int8_t)header[0x149];
    printf("\t RAM size : %2.2X\n", ramSize);

    u_int8_t licCode = (u_int8_t)header[0x14B];
    printf("\t LIC code : %2.2X\n", licCode);

    u_int8_t romVers = (u_int8_t)header[0x14C];
    printf("\t ROM vers : %2.2X\n", romVers);
    
    u_int8_t checkSum = (u_int8_t)header[0x14D];
    u_int16_t x = 0;
    for(u_int16_t i = 0x134 ; i <= 0x14C ; i++){
        x -= header[i] - 1;
    }
    printf("\t Checksum : %2.2X (%s)\n",checkSum, (x & 0xFF) ? "passed" : "failed");
    
    title = NULL;
    delete title;
}

std::string Memory::dump(){
    std::string res = "";
    res += "LY\n";
    res += std::to_string((int)this->get(Memory::LY));

    return res;
}

void Memory::updatePalette(unsigned char data, unsigned char palette){
    uint32_t* palettePtr;
    switch(palette){
        case(0): palettePtr = this->bgpColors;
            break;
        case(1): palettePtr = this->sp1Colors;
            break;
        case(2): palettePtr = this->sp2Colors;
            break;
    }

    palettePtr[0] = defaultColors[data & 0b11];
    palettePtr[1] = defaultColors[(data >> 2) & 0b11];
    palettePtr[2] = defaultColors[(data >> 4) & 0b11];
    palettePtr[3] = defaultColors[(data >> 6) & 0b11];
    
}

unsigned int Memory::getBgpColor(unsigned char i){
    return this->bgpColors[i];
}

unsigned int Memory::getSp1Color(unsigned char i){
    return this->sp1Colors[i];
}

unsigned int Memory::getSp2Color(unsigned char i){
    return this->sp2Colors[i];
}
