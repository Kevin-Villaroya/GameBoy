#ifndef __RR_REGISTER_H__
#define __RR_REGISTER_H__
#include "../Instruction.h"

class RrRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        RrRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif