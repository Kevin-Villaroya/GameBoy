#ifndef __HALT_H__
#define __HALT_H__

#include "../../Instruction.h"

class Halt : public Instruction{
    private:
        void* context;
    public:
        Halt(void* context);
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif