#ifndef __RR_A_H__
#define __RR_A_H__
#include "../Instruction.h"

class RrA : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrA();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif