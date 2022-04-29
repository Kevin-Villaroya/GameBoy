#ifndef __RR_CARRY_HL_H__
#define __RR_CARRY_HL_H__
#include "../Instruction.h"

class RrCarryHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrCarryHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif