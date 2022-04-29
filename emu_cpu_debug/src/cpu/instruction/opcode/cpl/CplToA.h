#ifndef __CPL_TO_A_H__
#define __CPL_TO_A_H__
#include "../Instruction.h"

class CplToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        CplToA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif