#ifndef __LOAD_IMMEDIATE_ADDRESS_TO_REGISTER_H__
#define __LOAD_IMMEDIATE_ADDRESS_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadImmediateAddressToRegister : public Instruction{
    private:
        unsigned short address;
        RegisterName registerName;
    public:
        LoadImmediateAddressToRegister(RegisterName registerName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif