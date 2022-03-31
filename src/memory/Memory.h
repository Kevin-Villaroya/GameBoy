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
    
    public:
        static const unsigned short DIVIDER = 0xFF04;
        static const unsigned short TIMA = 0xFF05;
        static const unsigned short TMA = 0xFF06;
        static const unsigned short TMC = 0xFF07;

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
};

#endif
