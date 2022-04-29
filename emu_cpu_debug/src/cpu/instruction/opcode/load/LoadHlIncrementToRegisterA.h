#ifndef __LOAD_HL_INCREMENT_TO_REGISTER_A_H__
#define __LOAD_HL_INCREMENT_TO_REGISTER_A_H__

#include "../../Instruction.h"

class LoadHlIncrementToRegisterA : public Instruction{
private:

public:
    void execute(Memory& ram, Registers& registers) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(const Memory&, unsigned short) override;
    std::string toString() override;
};

#endif