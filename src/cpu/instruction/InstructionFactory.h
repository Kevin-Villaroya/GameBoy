#ifndef __INSTRUCTION_FACTORY_H__
#define __INSTRUCTION_FACTORY_H__

#include "Instruction.h"

class InstructionFactory{
    private:
        
    public:
        static Instruction* forCode(unsigned char byteInstr);
};

#endif