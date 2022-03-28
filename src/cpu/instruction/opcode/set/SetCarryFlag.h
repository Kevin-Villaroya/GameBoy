#ifndef __SET_CARRY_FLAG_H__
#define __SET_CARRY_FLAG_H__
#include "../Instruction.h"

class SetCarryFlag : public Instruction{
    private:
        RegisterName registerName;
    public:
        SetCarryFlag();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif