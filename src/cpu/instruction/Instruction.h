#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "../../memory/Memory.h"

class Instruction{
    private:
        
    public:
        virtual bool execute() = 0;
        virtual unsigned char getSize() = 0;
        virtual void setParameters(Memory) = 0;
};

#endif