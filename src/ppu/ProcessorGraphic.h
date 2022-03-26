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
	Memory* ram;

	ProcessorGraphicState currentState;

	// Tick associated to the current line being drawed
	unsigned int ticks;

	// Number of pixels displayed in the current line
	unsigned int x;

	void oamSearch();
	void pixelTransfer();
	void vBlank();
	void hBlank();

	unsigned char getLY();
	void setLY(unsigned char value);

	unsigned char getLCDC();
	void setLCDC(unsigned char value);

	unsigned char getBGP();
	void setBGP(unsigned char value);

public:
	ProcessorGraphic(Display* screen, Memory* ram);
	~ProcessorGraphic();

	void tick();
};

#endif