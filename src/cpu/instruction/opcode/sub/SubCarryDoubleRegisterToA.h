#ifndef __SUB_CARRY_DOUBLE_REGISTER_TO_A_H__
#define __SUB_CARRY_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class SubCarryDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        SubCarryDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif 