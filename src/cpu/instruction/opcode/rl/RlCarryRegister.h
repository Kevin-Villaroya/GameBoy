#ifndef __RL_CARRY_REGISTER_H__
#define __RL_CARRY_REGISTER_H__
#include "../Instruction.h"

class RlCarryRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlCarryRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif