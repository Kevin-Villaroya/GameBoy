#ifndef __DECREMENT_HL_H__
#define __DECREMENT_HL_H__

#include "../../Instruction.h"

class DecrementHL : public Instruction{

    public:
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
