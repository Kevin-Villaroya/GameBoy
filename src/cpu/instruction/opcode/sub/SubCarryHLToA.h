#ifndef __SUB_CARRY_HL_TO_A_H__
#define __SUB_CARRY_HL_TO_A_H__
#include "../Instruction.h"

class SubCarryHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        SubCarryHLToA();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 