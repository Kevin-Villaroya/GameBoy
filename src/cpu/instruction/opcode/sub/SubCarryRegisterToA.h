#ifndef __SUB_CARRY_REGISTER_TO_A_H__
#define __SUB_CARRY_REGISTER_TO_A_H__
#include "../Instruction.h"

class SubCarryRegisterToA : public Instruction{
    private:
        RegisterName registerName;

    public:
        SubCarryRegisterToA(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 