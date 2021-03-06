#ifndef __DECREMENT_REGISTER_H__
#define __DECREMENT_REGISTER_H__

#include "../../Instruction.h"

class DecrementRegister : public Instruction{
    private:
        RegisterName registerName;

    public:
        DecrementRegister(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
