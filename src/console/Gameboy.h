#ifndef __GAMEBOY_H__
#define __GAMEBOY_H__

#include <vector>
#include "../cpu/Processor.h"
#include "../ppu/ProcessorGraphic.h"
#include "../display/event/Event.h"

class Gameboy{
private:
	Processor cpu;
	Display* view;
	ProcessorGraphic ppu;

	bool isRunning;
	bool canTick;
	bool canSkip;
	bool isDebugMode;
	bool waitingBreakingOpCode;

	std::vector<unsigned short> opCodeBreak;
	
public:
	Gameboy(char* path);
	bool run();
	
	void treatEvent(Event event);
	void debugMode();

	~Gameboy();
};

#endif