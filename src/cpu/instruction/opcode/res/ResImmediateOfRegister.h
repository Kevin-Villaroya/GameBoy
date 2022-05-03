#ifndef __RES_IMMEDIATE_OF_REGISTER_H__
#define __RES_IMMEDIATE_OF_REGISTER_H__
#include "../Instruction.h"

class ResImmediateOfRegister : public Instruction{
    private:
        unsigned char bit;
        RegisterName registerName;
    public:
        ResImmediateOfRegister(unsigned char bit, RegisterName registerName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif
