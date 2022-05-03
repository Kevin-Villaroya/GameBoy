#ifndef __CP_REGISTER_TO_A_H__
#define __CP_REGISTER_TO_A_H__
#include "../Instruction.h"

class CpRegisterToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        CpRegisterToA(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif