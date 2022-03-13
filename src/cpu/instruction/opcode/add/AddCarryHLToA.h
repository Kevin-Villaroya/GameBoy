#ifndef __ADD_CARRY_HL_TO_A_H__
#define __ADD_CARRY_HL_TO_A_H__
#include "../Instruction.h"

class AddCarryHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        AddCarryHLToA();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif 