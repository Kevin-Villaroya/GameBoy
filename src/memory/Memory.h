#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstdint>

#define CARTRIGBE_SIZE 32768
#define RAM_SIZE 65536

class Memory{
    private:
        unsigned char memory[RAM_SIZE];
        unsigned char bootRom[256];

        void resetMemory();

        void setBootMemory();
        void setMemory();
    
    public:
        const unsigned short TIMA = 0xFF05;
        const unsigned short TMA = 0xFF06;
        const unsigned short TMC = 0xFF07;

        Memory(char* path);

        void init();
        unsigned char getInstructionByteInstr(unsigned short pos) const;
        unsigned char get(unsigned short pos) const;

        void writeMemory(unsigned short, unsigned char);
        void set(unsigned short, unsigned char);

        unsigned char operator[](unsigned short) const;
        unsigned short getDouble(unsigned short pos) const;

        unsigned char* getBootRom();
        bool hasReadBootRom() const;
};

#endif
