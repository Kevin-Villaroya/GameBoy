#ifndef __LOAD_HL_IMMEDIATE_SP_H__
#define __LOAD_HL_IMMEDIATE_SP_H__

#include "../../Instruction.h"

class LoadHlImmediateSp : public Instruction{
private:
    char value;
public:
    void execute(Memory& ram, Registers& registers) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(Memory&, unsigned short) override;
    std::string toString() override;
};

#endif