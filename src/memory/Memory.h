#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstdint>

#define CARTRIGBE_SIZE 32768
#define RAM_SIZE 65536

class Memory{
    private:
        unsigned char memory[RAM_SIZE];

        void resetMemory();
        void setMemory();
    
    public:
        Memory(char* path);

        void init();
        unsigned char get(unsigned short pos);
        unsigned char operator[](unsigned short);
};

#endif