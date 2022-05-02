#ifndef __SHIFT_LEFT_HL_H__
#define __SHIFT_LEFT_HL_H__
#include "../Instruction.h"

class ShiftLeftHL : public Instruction{
    private:
        RegisterName registerName;
    public:
        ShiftLeftHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif