#ifndef __OR_HL_TO_A_H__
#define __OR_HL_TO_A_H__
#include "../Instruction.h"

class OrHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegisterName;
    public:
        OrHLToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif