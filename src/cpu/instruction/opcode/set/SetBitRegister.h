#ifndef __SET_BIT_REGISTER_H__
#define __SET_BIT_REGISTER_H__
#include "../Instruction.h"

class SetBitRegister : public Instruction{
    private:
        int bit;
        RegisterName registerName;
        
    public:
        SetBitRegister(int, RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif