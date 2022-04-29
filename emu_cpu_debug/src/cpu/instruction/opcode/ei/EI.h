#ifndef __EI_H__
#define __EI_H__

#include "../../Instruction.h"

class EI : public Instruction{
    private:
        void* context;
    public:
        EI(void*);
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif