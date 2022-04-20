#ifndef __SUB_IMMEDIATE_TO_A_H__
#define __SUB_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class SubImmediateToA : public Instruction{
    private:
        unsigned char parameter;

    public:
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 