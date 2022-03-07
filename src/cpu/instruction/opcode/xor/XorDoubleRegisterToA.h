#ifndef __XOR_DOUBLE_REGISTER_TO_A_H__
#define __XOR_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class XorDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        XorDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif