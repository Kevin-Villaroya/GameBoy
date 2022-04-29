#ifndef __PUSH_DOUBLE_REGISTER_TO_STACK_H__
#define __PUSH_DOUBLE_REGISTER_TO_STACK_H__
#include "../Instruction.h"

class PushDoubleRegisterToStack : public Instruction{
    private:
        DoubleRegisterName doubleRegName;
    public:
        PushDoubleRegisterToStack(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif
