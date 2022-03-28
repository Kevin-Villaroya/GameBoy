#ifndef __LOAD_REGISTER_TO_REGISTER_H__
#define __LOAD_REGISTER_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadRegisterToRegister : public Instruction{
    private:
        RegisterName src;
        RegisterName dest;

    public:
        LoadRegisterToRegister(RegisterName, RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
