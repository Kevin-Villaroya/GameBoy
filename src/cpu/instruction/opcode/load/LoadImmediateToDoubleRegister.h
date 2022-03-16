#ifndef __LOAD_IMMEDIATE_TO_DOUBLE_REGISTER_H__
#define __LOAD_IMMEDIATE_TO_DOUBLE_REGISTER_H__

#include "../../Instruction.h"

class LoadImmediateToDoubleRegister : public Instruction{
    private:
        unsigned short parameter;
        DoubleRegisterName registerName;
    public:
        LoadImmediateToDoubleRegister(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};

#endif
