#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "../cpu/Processor.h"
#include "../ppu/ProcessorGraphic.h"

class Console{
private:
	Processor cpu;
	ProcessorGraphic ppu;
public:
	Console(char* path);
	bool run();
};

#endif