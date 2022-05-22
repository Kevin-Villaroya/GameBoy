#ifndef __ADD_CARRY_REGISTER_TO_A_H__
#define __ADD_CARRY_REGISTER_TO_A_H__
#include "../Instruction.h"

class AddCarryRegisterToA : public Instruction{
    private:
        RegisterName registerName;

    public:
        AddCarryRegisterToA(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif 