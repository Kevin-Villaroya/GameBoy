#ifndef __AND_DOUBLE_REGISTER_TO_A_H__
#define __AND_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class AndDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        AndDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif