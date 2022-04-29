#ifndef __RES_IMMEDIATE_OF_HL_H__
#define __RES_IMMEDIATE_OF_HL_H__
#include "../Instruction.h"

class ResImmediateOfHL : public Instruction{
    private:
        unsigned char bit;
    public:
        ResImmediateOfHL(unsigned char bit);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif
