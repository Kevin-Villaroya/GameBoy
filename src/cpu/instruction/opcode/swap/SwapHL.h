#ifndef __SWAP_HL_H__
#define __SWAP_HL_H__
#include "../Instruction.h"

class SwapHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        SwapHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif