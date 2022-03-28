#ifndef __XOR_HL_TO_A_H__
#define __XOR_HL_TO_A_H__
#include "../Instruction.h"

class XorHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        XorHLToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif