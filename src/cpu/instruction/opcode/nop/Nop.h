#ifndef __NOP_H__
#define __NOP_H__

#include "../Instruction.h"

class Nop : public Instruction{
    void execute(Memory& ram, Registers& registers) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(const Memory&, unsigned short) override;
};

#endif