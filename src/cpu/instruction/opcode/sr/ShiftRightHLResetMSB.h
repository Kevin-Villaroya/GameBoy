#ifndef __SHIFT_RIGHT_HL_RESET_MSB_H__
#define __SHIFT_RIGHT_HL_RESET_MSB_H__
#include "../Instruction.h"

class ShiftRightHLResetMSB : public Instruction{
    private:
        RegisterName registerName;
    public:
        ShiftRightHLResetMSB();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif