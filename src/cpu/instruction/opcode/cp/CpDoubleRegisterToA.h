#ifndef __CP_DOUBLE_REGISTER_TO_A_H__
#define __Cp_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class CpDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        CpDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif