#ifndef __DECREMENT_DOUBLE_REGISTER_H__
#define __DECREMENT_DOUBLE_REGISTER_H__

#include "../../Instruction.h"

class DecrementDoubleRegister : public Instruction{
    private:
        DoubleRegisterName registerName;

    public:
        DecrementDoubleRegister(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
