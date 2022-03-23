#ifndef __BIT_HL_H__
#define __BIT_HL_H__

#include "../../Instruction.h"

class BitHl : public Instruction{
private:
    unsigned char bit;
public:
    BitHl(unsigned char bit);

    void execute(Memory&, Registers&) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(const Memory&, unsigned short) override;
};

#endif