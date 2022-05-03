#ifndef __AND_IMMEDIATE_TO_A_H__
#define __AND_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class AndImmediateToA : public Instruction{
    private:
        unsigned char parameter;
    public:
        AndImmediateToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif