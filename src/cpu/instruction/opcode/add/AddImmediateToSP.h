#ifndef __ADD_IMMEDIATE_TO_SP_H__
#define __ADD_IMMEDIATE_TO_SP_H__
#include "../Instruction.h"

class AddImmediateToSP : public Instruction{
    private:
        char parameter;

    public:
        AddImmediateToSP();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, char);
};

#endif 