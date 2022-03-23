#ifndef __LOAD_A_REGISTER_TO_INCREMENT_HL_H__
#define __LOAD_A_REGISTER_TO_INCREMENT_HL_H__

#include "../../Instruction.h"

class LoadARegisterToHlIncrement : public Instruction{
private:

public:
    void execute(Memory& ram, Registers& registers) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(const Memory&, unsigned short) override;
};

#endif