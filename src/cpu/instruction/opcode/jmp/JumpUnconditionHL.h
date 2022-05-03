#ifndef __JUMP_UNCONDITIONAL_HL_H__
#define __JUMP_UNCONDITIONAL_HL_H__

#include "../Instruction.h"

class JumpUnconditionHL : public Instruction{
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif