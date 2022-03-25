#ifndef __PPU_H__
#define __PPU_H__

#include "PixelFetcher.h"
#include "../display/Display.h"

enum class ProcessorGraphicState{
	OAMSearch,
	PixelTransfer,
	HBlank,
	VBlank
};

class ProcessorGraphic{
private:
	const unsigned int SIZE_SCREEN_X = 160;
	const unsigned int SIZE_SCREEN_Y = 144;

	PixelFetcher fetcher;
	Display* screen;

	ProcessorGraphicState currentState;

	// Tick associated to the current line being drawed
	unsigned int ticks;

	// Number of pixels displayed in the current line
	unsigned int x;

	void oamSearch(Memory& ram);
	void pixelTransfer(Memory& ram);
	void vBlank(Memory& ram);
	void hBlank(Memory& ram);

	unsigned char getLY(Memory& ram);
	void setLY(Memory& ram, unsigned char value);
public:
	ProcessorGraphic(Display* screen);
	~ProcessorGraphic();

	void tick(Memory& ram);
};

#endif