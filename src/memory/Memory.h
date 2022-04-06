#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstdint>

#define CARTRIGBE_SIZE 32768
#define RAM_SIZE 65536

class Memory{
    private:
        int timerCounter;
        int dividerCounter;

        unsigned char memory[RAM_SIZE];
        unsigned char bootRom[256];

        void resetMemory();

        void setBootMemory();
        void setMemory();

        bool isClockEnabled(); //check the bit 2 of TMC
        unsigned char getClockFrequency();
        void setClockFrequency();
        void doDividerRegister(int cycles);

        void dmaTransfer(unsigned char value);
    
    public:
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

        void init();
        unsigned char getInstructionByteInstr(unsigned short pos) const;
        unsigned char get(unsigned short pos) const;

        void writeMemory(unsigned short, unsigned char);
        void set(unsigned short, unsigned char);

        unsigned char operator[](unsigned short) const;
        unsigned short getDouble(unsigned short pos) const;

        int getTimerCounter();

        unsigned char* getBootRom();
        bool hasReadBootRom() const;

        void updateTimers(int cycles);
        void requestInterupt(unsigned char bit);
};

#endif
