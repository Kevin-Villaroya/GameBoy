#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "../memory/Memory.h"
#include "../memory/Registers.h"
#include "instruction/Instruction.h"
#include <fstream>
#define IT_VBLANK 1
#define IT_LCD_STAT 2
#define IT_TIMER 4
#define IT_SERIAL 8
#define IT_JOYPAD 16



class Processor{
    private:
        Memory* memory;
        Registers* registers;

        Instruction* instruction;
        unsigned int ticksDelayed;

        Instruction* fetch();

        Instruction* decodeAndLoad();
        void execute(Instruction&);

        bool startupSequence();
        bool halted;
        bool steppingMode;
        bool interruptMasterEnable;
        bool enableIME;
	
		const std::string getNameForCartridgeType(unsigned char);	

        //debug
        char dbgMsg[10024] = {0};
        int dbgMsgSize = 0;
        void dbgUpdate();
        void dbgPrint();
        
        void interruptHandle(unsigned short);
        bool interruptCheck(unsigned short address, int interruptType);
	
    public:
        Processor(Memory* memory, Registers* registers);
	
        int tick();
		void printMetadata();

        //1 step of the cpu, return the number of cpu ticks or -1 if error
        int step();
        //timer tick
        void timerTick();

        Instruction* getInstruction();

        Memory& getMemory();

        void dumpRegister();
        void dumpRam();

        void printRegisters();

        void setIME(bool);
        void setHalt(bool);
        bool isHalt();
        void setEnableIME(bool);
        
        void doInterrupt();
};

#endif
