#ifndef __SHIFT_RIGHT_REGISTER_RESET_MSB_H__
#define __SHIFT_RIGHT_REGISTER_RESET_MSB_H__
#include "../Instruction.h"

class ShiftRightRegisterResetMSB : public Instruction{
    private:
        RegisterName registerName;
    public:
        ShiftRightRegisterResetMSB(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif