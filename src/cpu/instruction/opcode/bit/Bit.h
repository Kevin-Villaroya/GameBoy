#ifndef __BIT_H__
#define __BIT_H__

#include "../../Instruction.h"

class Bit : public Instruction{
private:
    unsigned char bit;
    RegisterName registerName;
public:
    Bit(unsigned char bit, RegisterName registerName);

    void execute(Memory&, Registers&) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(const Memory&, unsigned short) override;
};

#endif