#ifndef __LOAD_HL_TO_SP_H__
#define __LOAD_HL_TO_SP_H__

#include "../../Instruction.h"

class LoadHlToSp : public Instruction{
private:

public:
    void execute(Memory& ram, Registers& registers) override;
    unsigned int getSize() override;
    unsigned int getTiming() override;
    void setParameters(Memory&, unsigned short) override;
    std::string toString() override;
};

#endif