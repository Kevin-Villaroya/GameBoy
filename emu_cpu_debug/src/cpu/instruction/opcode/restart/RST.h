#ifndef __RST_H__
#define __RST_H__
#include "../Instruction.h"

class RST : public Instruction{
    private:
        unsigned char address;
    public:
        RST(unsigned char address);

        void execute(Memory&, Registers&) override;
        unsigned int getSize() override;
        unsigned int getTiming() override;
        void setParameters(const Memory&, unsigned short) override;
        std::string toString() override;
};


#endif
