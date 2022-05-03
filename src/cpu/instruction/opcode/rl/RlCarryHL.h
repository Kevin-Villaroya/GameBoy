#ifndef __RL_CARRY_HL_H__
#define __RL_CARRY_HL_H__
#include "../Instruction.h"

class RlCarryHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlCarryHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif