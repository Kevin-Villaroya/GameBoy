#ifndef __RL_REGISTER_H__
#define __RL_REGISTER_H__
#include "../Instruction.h"

class RlRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif