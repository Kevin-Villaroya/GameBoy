#ifndef __LOAD_REGISTER_TO_IMMEDIATE_ADDRESS_H__
#define __LOAD_REGISTER_TO_IMMEDIATE_ADDRESS_H__

#include "../../Instruction.h"

class LoadRegisterToImmediateAddress : public Instruction{
    private:
        unsigned short address;
        RegisterName registerName;
    public:
        LoadRegisterToImmediateAddress(RegisterName registerName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif