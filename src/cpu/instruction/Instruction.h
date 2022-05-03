#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <string>
#include "../../memory/Memory.h"
#include "../../memory/Registers.h"

class Instruction{
    private:
    public:
        virtual void execute(Memory& ram, Registers& registers) = 0;
        virtual unsigned int getSize() = 0;
        virtual unsigned int getTiming() = 0;
        virtual void setParameters(Memory&, unsigned short pc) = 0;
        virtual std::string toString() = 0;

        unsigned short opCode;
};

#endif
