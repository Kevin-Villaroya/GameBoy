#ifndef __DAA_TO_A_H__
#define __DAA_TO_A_H__
#include "../Instruction.h"

class DaaToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        DaaToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif