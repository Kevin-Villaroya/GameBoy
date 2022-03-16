#ifndef __INCREMENT_DOUBLE_REGISTER_H__
#define __INCREMENT_DOUBLE_REGISTER_H__

#include "../../Instruction.h"

class IncrementDoubleRegister : public Instruction{
    private:
        DoubleRegisterName registerName;

    public:
        IncrementDoubleRegister(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif
