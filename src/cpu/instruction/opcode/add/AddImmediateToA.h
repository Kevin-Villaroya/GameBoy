#ifndef __ADD_IMMEDIATE_TO_A_H__
#define __ADD_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class AddImmediateToA : public Instruction{
    private:
        unsigned char parameter;

    public:
        AddImmediateToA();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory& memory, unsigned short pc) override;
};

#endif 
