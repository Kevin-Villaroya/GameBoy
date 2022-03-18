#ifndef __INSTRUCTION_FACTORY_H__
#define __INSTRUCTION_FACTORY_H__

#include "Instruction.h"

class InstructionFactory{
    private:
        static Instruction* forCodeCb(unsigned char byteInstr);
    public:
        static Instruction* forCode(const Memory& memory ,unsigned short pc);
        
};

#endif
