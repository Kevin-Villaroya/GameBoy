#ifndef __SHIFT_RIGHT_REGISTER_H__
#define __SHIFT_RIGHT_REGISTER_H__
#include "../Instruction.h"

class ShiftRightRegister : public Instruction{
    private:
        RegisterName registerName;
    public:
        ShiftRightRegister(RegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif