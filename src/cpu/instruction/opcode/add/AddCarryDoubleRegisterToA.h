#ifndef __ADD_CARRY_DOUBLE_REGISTER_TO_A_H__
#define __ADD_CARRY_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class AddCarryDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        AddCarryDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif 