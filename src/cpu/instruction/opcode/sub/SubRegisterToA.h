#ifndef __SUB_REGISTER_TO_A_H__
#define __SUB_REGISTER_TO_A_H__
#include "../Instruction.h"

class SubRegisterToA : public Instruction{
    private:
        RegisterName registerName;

    public:
        SubRegisterToA(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 