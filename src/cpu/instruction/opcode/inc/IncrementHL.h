#ifndef __INCREMENT_HL_H__
#define __INCREMENT_HL_H__

#include "../Instruction.h"

class IncrementHL : public Instruction{

    public:
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif
