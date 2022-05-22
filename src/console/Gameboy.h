#ifndef __GAMEBOY_H__
#define __GAMEBOY_H__

#include <vector>
#include "../cpu/Processor.h"
#include "../ppu/ProcessorGraphic.h"
#include "../display/event/Event.h"
#include "../ppu/OamDma.h"

class Gameboy{
private:
	const int CLOCKSPEED = 4194304;

	int start;
	int instructionDone;

	Memory memory;
	Registers registers;
	Processor cpu;
	Display* view;
	ProcessorGraphic ppu;
	
	int frequency;

	//context
	bool running;
	bool paused;
	bool die;
	uint64_t ticks;

	bool canTick;
	bool canSkip;
	bool isDebugMode;
	bool waitingBreakingOpCode;
	bool canContinue;

	std::vector<unsigned short> opCodeBreak;
	std::vector<unsigned short> pcValueBreak;

	void updateTimers(bool instructionExecuted);
	void debug(bool isInstructionExecuted);
	void doInterrupts();
	void serviceInterrupt(int interruption);

	bool needBreak();
	void launchCpuThread();

	OamDma oamDma;
	
public:
	Gameboy(char* path);
	bool run();
	
	void gameboyTick(unsigned int n);
	void debugMode();

	void printTest();
	bool isRunning();
	bool isPaused();
	int getTicks();
	Gameboy* getContext();

	~Gameboy();
};

#endif