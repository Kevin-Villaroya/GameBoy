#ifndef __DI_H__
#define __DI_H__

#include "../../Instruction.h"

class DI : public Instruction{
    private:
        void* cpuContext;
    public:
        DI(void* context);
        void execute(Memory& ram, Registers& registers) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};

#endif