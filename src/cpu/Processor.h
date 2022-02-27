#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "../memory/Memory.h"
#include "../memory/Registers.h"
#include "instruction/Instruction.h"
#include <fstream>

class Processor{
    private:
        Memory memory;
        Registers registers;

        Instruction* fetch();

        Instruction* decodeAndLoad(unsigned char);
        void execute(Instruction&);

        bool startupSequence();
    public:
        Processor(char* path);
        void run();
};

#endif