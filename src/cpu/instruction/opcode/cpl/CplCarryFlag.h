#ifndef __CPL_CARRY_FLAG_H__
#define __CPL_CARRY_FLAG_H__
#include "../Instruction.h"

class CplCarryFlag : public Instruction{
    private:
        RegisterName registerName;
    public:
        CplCarryFlag();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif