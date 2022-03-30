#ifndef __SET_BIT_HL_H__
#define __SET_BIT_HL_H__
#include "../Instruction.h"

class SetBitHL : public Instruction{
    private:
        int bit;
    public:
        SetBitHL(int);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif