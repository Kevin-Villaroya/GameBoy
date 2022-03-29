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
        Memory(char* path);

        void init();
        unsigned char getInstructionByteInstr(unsigned short pos) const;
        unsigned char get(unsigned short pos) const;
        void set(unsigned short, unsigned char);
        unsigned char operator[](unsigned short) const;
		unsigned char& operator[](unsigned short);
        unsigned short getDouble(unsigned short pos) const;

        unsigned char* getBootRom();
        bool hasReadBootRom() const;
};

#endif
