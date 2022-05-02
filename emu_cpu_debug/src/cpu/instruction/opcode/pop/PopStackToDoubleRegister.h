#ifndef __POP_STACK_TO_DOUBLE_REGISTER_H__
#define __POP_STACK_TO_DOUBLE_REGISTER_H__
#include "../Instruction.h"

class PopStackToDoubleRegister : public Instruction{
    private:
        DoubleRegisterName doubleRegName;
    public:
        PopStackToDoubleRegister(DoubleRegisterName);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif
