#ifndef __JUMP_UNCONDITIONAL_RELATIVE_H__
#define __JUMP_UNCONDITIONAL_RELATIVE_H__

#include "../Instruction.h"

class JumpUnconditionalRelativeImmediate : public Instruction{
    private:
        signed char parameter;
	
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif
