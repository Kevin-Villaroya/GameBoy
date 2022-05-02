#ifndef __XOR_REGISTER_TO_A_H__
#define __XOR_REGISTER_TO_A_H__
#include "../Instruction.h"

class XorRegisterToA : public Instruction{
    private:
        RegisterName registerName;
    public:
        XorRegisterToA(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif