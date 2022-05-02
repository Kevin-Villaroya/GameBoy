#ifndef __STOP_H__
#define __STOP_H__
#include "../Instruction.h"

class Stop : public Instruction{
    private:
        RegisterName registerName;
    public:
        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(Memory&, unsigned short) override;
        std::string toString() override;
};


#endif