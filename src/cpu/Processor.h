#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "../memory/Memory.h"
#include "../memory/Registers.h"
#include "instruction/Instruction.h"
#include <fstream>

class Processor{
    private:
        Memory memory;
        Registers registers;

        Instruction* instruction;
        unsigned int ticksDelayed;

        Instruction* fetch();

        Instruction* decodeAndLoad();
        void execute(Instruction&);

        bool startupSequence();
	
		const std::string getNameForCartridgeType(unsigned char);	
	
    public:
        Processor(char* path);
	
        bool tick();
        void run();
		void printMetadata();

        Memory& getMemory();

        void dump();
};

#endif
