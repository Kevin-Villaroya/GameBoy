#ifndef __LOAD_FROM_IMMEDIATE_RELATIVE_ADDRESS_TO_REGISTER_H__
#define __LOAD_FROM_IMMEDIATE_RELATIVE_ADDRESS_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadFromImmediateRelativeAddressToRegister : public Instruction{
    private:
        unsigned char relativeAddress;
        RegisterName registerName;
    public:
        LoadFromImmediateRelativeAddressToRegister(RegisterName registerName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif