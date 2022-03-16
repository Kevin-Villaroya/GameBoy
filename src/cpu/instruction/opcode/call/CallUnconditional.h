#ifndef __CALL_UNCONDITIONAL_H__
#define __CALL_UNCONDITIONAL_H__
#include "../../Instruction.h"

class CallUnconditional : public Instruction {
    private:
        unsigned short address;
	
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif
