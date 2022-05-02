#ifndef __OR_REGISTER_TO_A_H__
#define __OR_REGISTER_TO_A_H__
#include "../Instruction.h"

class OrRegisterToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        OrRegisterToA(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif