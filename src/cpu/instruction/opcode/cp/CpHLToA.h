#ifndef __CP_HL_TO_A_H__
#define __Cp_HL_TO_A_H__
#include "../Instruction.h"

class CpHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        CpHLToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif