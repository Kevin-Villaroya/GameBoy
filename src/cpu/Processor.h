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
        uint8_t rom[CARTRIGBE_SIZE];

        Instruction* fetch();

        Instruction* decode(unsigned char);
        bool execute(Instruction&);
    public:
        Processor(uint8_t instr[CARTRIGBE_SIZE]);
        bool run();
};

#endif