#ifndef __JUMP_CONDITIONAL_RELATIVE_IMMEDIATE_H__
#define __JUMP_CONDITIONAL_RELATIVE_IMMEDIATE_H__

#include "../../Instruction.h"
#include "../../condition/InstructionCondition.h"

class JumpConditionalRelativeImmediate : public Instruction{
    private:
        Condition condition;
        signed char address;
        int timing = 12;
    public:
        JumpConditionalRelativeImmediate(Condition condition);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif