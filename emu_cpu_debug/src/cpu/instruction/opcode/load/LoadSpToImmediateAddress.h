#ifndef __LOAD_SP_TO_IMMEDIATE_ADDRESS_H__
#define __LOAD_SP_TO_IMMEDIATE_ADDRESS_H__

#include "../../Instruction.h"

class LoadSpToImmediateAddress : public Instruction{
    private:
        unsigned short address;

    public:
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
