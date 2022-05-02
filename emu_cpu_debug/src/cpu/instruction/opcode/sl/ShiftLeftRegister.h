#ifndef __SHIFT_LEFT_REGISTER_H__
#define __SHIFT_LEFT_REGISTER_H__
#include "../Instruction.h"

class ShiftLeftRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        ShiftLeftRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif