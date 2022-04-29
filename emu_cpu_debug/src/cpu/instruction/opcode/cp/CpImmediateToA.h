#ifndef __CP_IMMEDIATE_TO_A_H__
#define __Cp_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class CpImmediateToA : public Instruction{
    private:
        unsigned char parameter;
    public:
        CpImmediateToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif