#ifndef __SHIFT_RIGHT_HL_H__
#define __SHIFT_RIGHT_HL_H__
#include "../Instruction.h"

class ShiftRightHL : public Instruction{
    private:
    
    public:
        ShiftRightHL();

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif