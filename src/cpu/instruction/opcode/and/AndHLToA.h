#ifndef __AND_HL_TO_A_H__
#define __AND_HL_TO_A_H__
#include "../Instruction.h"

class AndHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        AndHLToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif