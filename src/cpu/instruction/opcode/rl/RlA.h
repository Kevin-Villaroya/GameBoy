#ifndef __RL_A_H__
#define __RL_A_H__
#include "../Instruction.h"

class RlA : public Instruction{
    private:
        RegisterName registerName;
    public:
        RlA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif