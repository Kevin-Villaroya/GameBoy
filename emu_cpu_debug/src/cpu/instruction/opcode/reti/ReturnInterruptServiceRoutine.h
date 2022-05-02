#ifndef RETURN_INTERRUPT_SERVICE_ROUTINE_H__
#define RETURN_INTERRUPT_SERVICE_ROUTINE_H__

#include "../../Instruction.h"

class ReturnInterruptServiceRoutine : public Instruction{
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};

#endif