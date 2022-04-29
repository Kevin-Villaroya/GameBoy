#ifndef __RL_CARRY_A_H__
#define __RL_CARRY_A_H__
#include "../Instruction.h"

class RlCarryA : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlCarryA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif