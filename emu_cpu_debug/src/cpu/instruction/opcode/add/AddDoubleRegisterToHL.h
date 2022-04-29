#ifndef __ADD_DOUBLE_REGISTER_TO_HL_H__
#define __ADD_DOUBLE_REGISTER_TO_HL_H__
#include "../Instruction.h"

class AddDoubleRegisterToHL : public Instruction{
    private:
        DoubleRegisterName doubleRegName;

    public:
        AddDoubleRegisterToHL(DoubleRegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 