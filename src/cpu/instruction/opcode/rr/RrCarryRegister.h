#ifndef __RR_CARRY_REGISTER_H__
#define __RR_CARRY_REGISTER_H__
#include "../Instruction.h"

class RrCarryRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrCarryRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif