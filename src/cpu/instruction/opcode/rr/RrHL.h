#ifndef __RR_HL_H__
#define __RR_HL_H__
#include "../Instruction.h"

class RrHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif