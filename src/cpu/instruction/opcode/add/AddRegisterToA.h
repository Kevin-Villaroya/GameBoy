#ifndef __ADD_REGISTER_TO_A_H__
#define __ADD_REGISTER_TO_A_H__
#include "../Instruction.h"

class AddRegisterToA : public Instruction{
    private:
        RegisterName registerName;

    public:
        AddRegisterToA(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 