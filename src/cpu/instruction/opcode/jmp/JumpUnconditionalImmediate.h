#ifndef __JUMP_UNCONDITIONAL_H__
#define __JUMP_UNCONDITIONAL_H__

#include "../Instruction.h"

class JumpUnconditionalImmediate : public Instruction{
    private:
        unsigned short parameter;
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif