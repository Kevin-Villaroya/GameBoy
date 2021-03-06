#ifndef __INCREMENT_REGISTER_H__
#define __INCREMENT_REGISTER_H__

#include "../Instruction.h"

class IncrementRegister : public Instruction{
    private:
        RegisterName registerName;

    public:
        IncrementRegister(RegisterName);

        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif