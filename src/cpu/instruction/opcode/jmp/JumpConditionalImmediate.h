#ifndef __JUMP_CONDITIONAL_IMMEDIATE_H__
#define __JUMP_CONDITIONAL_IMMEDIATE_H__

#include "../../Instruction.h"
#include <functional>

class JumpConditionalImmediate : public Instruction{
	private:
		std::function<bool(const Memory&, const Registers&)> test;
		unsigned short address;
	
    public:
		JumpConditionalImmediate(std::function<bool(const Memory&, const Registers&)> test);
	
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif
