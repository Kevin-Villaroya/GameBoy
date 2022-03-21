#ifndef __JUMP_CONDITIONAL_IMMEDIATE_H__
#define __JUMP_CONDITIONAL_IMMEDIATE_H__

#include "../../Instruction.h"
#include "../../condition/InstructionCondition.h"

class JumpConditionalImmediate : public Instruction{
	private:
		Condition test;
		unsigned short address;
	
    public:
		  JumpConditionalImmediate(Condition test);
	
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif
