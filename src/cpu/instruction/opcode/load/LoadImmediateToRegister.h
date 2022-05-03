#ifndef __LOAD_IMMEDIATE_TO_REGISTER_H__
#define __LOAD_IMMEDIATE_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadImmediateToRegister : public Instruction{
    private:
        unsigned char parameter;
        RegisterName registerName;
	
    public:
        LoadImmediateToRegister(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
