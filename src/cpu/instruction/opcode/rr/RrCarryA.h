#ifndef __RR_CARRY_A_H__
#define __RR_CARRY_A_H__
#include "../Instruction.h"

class RrCarryA : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrCarryA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif