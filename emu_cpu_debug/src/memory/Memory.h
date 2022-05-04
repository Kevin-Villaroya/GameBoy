#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "../ppu/OamDma.h"

#include <cstdint>
#include <string>

#define CARTRIGBE_SIZE 32768
#define RAM_SIZE 65536

class Memory{
    friend class OamDma;
    private:
        int timerCounter;
        int dividerCounter;
        unsigned char dividerClock;
        uint32_t bgpColors[4];
        uint32_t sp1Colors[4];
        uint32_t sp2Colors[4];
        void updatePalette(unsigned char, unsigned char);
        const unsigned long defaultColors[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000}; 

        unsigned char memory[RAM_SIZE];
        unsigned char bootRom[256];

        unsigned char joypadState;

        void resetMemory();

        void setBootMemory();
        void setMemory();

        bool isClockEnabled(); //check the bit 2 of TMC
        unsigned char getClockFrequency();
        void setClockFrequency();
        void doDividerRegister(int cycles);

        unsigned char getJoypadState();
        void dmaTransfer(unsigned char value);
        void printCartridgeHeader(unsigned char* memory);

        OamDma* oamDma;

        void incrLy();
            
    public:
        static const unsigned short JOYPAD = 0xFF00;
        static const unsigned short DIVIDER = 0xFF04;
        static const unsigned short TIMA = 0xFF05;
        static const unsigned short TMA = 0xFF06;
        static const unsigned short TMC = 0xFF07;
        static const unsigned short IF = 0xFF0F;
        static const unsigned short DMA = 0xFF46;
        static const unsigned short LCDC = 0xFF40;
        static const unsigned short LCD = 0xFF41;
        static const unsigned short SCY = 0xFF42;
        static const unsigned short SCX = 0xFF43;
        static const unsigned short LY = 0xFF44;
        static const unsigned short LYC = 0xFF45;
        static const unsigned short BGP = 0xFF47;
        static const unsigned short WY = 0xFF4A;
        static const unsigned short WX = 0xFF4B;
        static const unsigned short IE = 0xFFFF;

        Memory(char* path);

        void init(OamDma*);
        unsigned char getInstructionByteInstr(unsigned short pos);
        unsigned char get(unsigned short pos);

        void writeMemory(unsigned short, unsigned char);
        void set(unsigned short, unsigned char);

        unsigned char operator[](unsigned short);
        unsigned short getDouble(unsigned short pos);

        int getTimerCounter();

        void incrementDIV();
        void incrementTIMA();

        unsigned char* getBootRom();
        bool hasReadBootRom();

        void updateTimers(int cycles);
        void requestInterupt(unsigned char bit);

        void setJoypad(unsigned char value);
        unsigned char getJoypad();

        unsigned char getDividerClock();
        void incDividerClock();

        unsigned int getBgpColor(unsigned char);
        unsigned int getSp1Color(unsigned char);
        unsigned int getSp2Color(unsigned char);

        std::string dump();
};

#endif
