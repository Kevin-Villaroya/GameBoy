#ifndef __ADD_HL_TO_A_H__
#define __ADD_HL_TO_A_H__
#include "../Instruction.h"

class AddHLToA : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        AddHLToA();

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 