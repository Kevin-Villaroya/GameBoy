#ifndef __AND_REGISTER_TO_A_H__
#define __AND_REGISTER_TO_A_H__
#include "../Instruction.h"

class AndRegisterToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        AndRegisterToA(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif