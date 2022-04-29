#ifndef __RL_RHL_H__
#define __RL_HL_H__
#include "../Instruction.h"

class RlHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif