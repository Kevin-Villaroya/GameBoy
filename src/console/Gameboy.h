#ifndef __GAMEBOY_H__
#define __GAMEBOY_H__

#include <vector>
#include "../cpu/Processor.h"
#include "../ppu/ProcessorGraphic.h"
#include "../display/event/Event.h"

class Gameboy{
private:
	const int CLOCKSPEED = 4194304;
	const uint32_t DELAY_FETCH = 30;

	Memory memory;
	Processor cpu;
	Display* view;
	ProcessorGraphic ppu;
	
	int frequency;

	uint32_t lastTimeFetch;

	bool isRunning;
	bool canTick;
	bool canSkip;
	bool isDebugMode;
	bool waitingBreakingOpCode;

	std::vector<unsigned short> opCodeBreak;

	void updateTimers(bool instructionExecuted);

	void debug(bool isInstructionExecuted);
	
public:
	Gameboy(char* path);
	bool run();
	
	void treatEvent(uint32_t currentTime);
	void debugMode();

	~Gameboy();
};

#endif