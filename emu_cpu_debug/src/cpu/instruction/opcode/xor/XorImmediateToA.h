#ifndef __XOR_IMMEDIATE_TO_A_H__
#define __XOR_IMMEDIATE_TO_A_H__
#include "../Instruction.h"

class XorImmediateToA : public Instruction{
    private:
        unsigned char parameter;
    public:
        XorImmediateToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif