#ifndef __OR_DOUBLE_REGISTER_TO_A_H__
#define __OR_DOUBLE_REGISTER_TO_A_H__
#include "../Instruction.h"

class OrDoubleRegisterToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        OrDoubleRegisterToA(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif