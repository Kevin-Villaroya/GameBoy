#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

class Instruction{
    private:
        
    public:
        virtual bool execute() = 0;
        virtual unsigned char getSize() = 0;
};

#endif