#ifndef __OR_IMMEDIATE_TO_A_H__
#define __OR_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class OrImmediateToA : public Instruction{
    private:
        unsigned char parameter;
    public:
        OrImmediateToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif