#ifndef __SWAP_REGISTER_H__
#define __SWAP_REGISTER_H__
#include "../Instruction.h"

class SwapRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        SwapRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
};


#endif