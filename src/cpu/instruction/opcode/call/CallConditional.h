#ifndef __CALL_CONDITIONAL_H__
#define __CALL_CONDITIONAL_H__

#include "../../Instruction.h"
#include "../../condition/InstructionCondition.h"

class CallConditional : public Instruction {
    private:
        Condition condition;
        unsigned short address;
	
    public:
        CallConditional(Condition);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif
