#ifndef __PPU_H__
#define __PPU_H__

#include "TileFetcher.h"
#include "SpriteFetcher.h"
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

	TileFetcher tileFetcher;
	SpriteFetcher spriteFetcher;
	Display* screen;
	Memory* ram;

	ProcessorGraphicState currentState;

	// Tick associated to the current line being drawed
	unsigned int ticks;

	// Number of pixels displayed in the current line
	unsigned int x;

	// All pixels in the current scanline
	unsigned char pixelLine[160];

	void oamSearch();
	void pixelTransfer();
	void vBlank();
	void hBlank();

	void setLCDStatus();
	bool isLCDEnabled();

public:
	ProcessorGraphic(Display* screen, Memory* ram);
	~ProcessorGraphic();

	void tick();
};

#endif