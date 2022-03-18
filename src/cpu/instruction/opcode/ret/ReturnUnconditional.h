#ifndef __RETURN_UNCONDITIONAL_H__
#define __RETURN_UNCONDITIONAL_H__

#include "../../Instruction.h"

class ReturnUnconditional : public Instruction{
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif
