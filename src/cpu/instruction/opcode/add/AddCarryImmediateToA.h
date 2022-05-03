#ifndef __ADD_CARRY_IMMEDIATE_TO_A_H__
#define __ADD_CARRY_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class AddCarryImmediateToA : public Instruction{
    private:
        unsigned char parameter;

    public:
        AddCarryImmediateToA();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 