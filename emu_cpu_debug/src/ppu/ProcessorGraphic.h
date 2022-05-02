#ifndef __PPU_H__
#define __PPU_H__

#include "TileFetcher.h"
#include "SpriteFetcher.h"
#include "../Processor.h"
#include "../display/Display.h"
#define SIZE_SCREEN_X 160
#define SIZE_SCREEN_Y 144
#define MAX_LINE_TICKS 456
#define MAX_FRAME_LINE 154


enum class ProcessorGraphicState{
	OAMSearch,
	PixelTransfer,
	HBlank,
	VBlank
};

class ProcessorGraphic{
private:
	
	TileFetcher tileFetcher;
	SpriteFetcher spriteFetcher;
	Display* screen;
	Memory* ram;
	void setCurrentState(ProcessorGraphicState);
	void incrementLy();
	

	ProcessorGraphicState currentState;

	unsigned int currentFrame;
	unsigned int videoBuffer[SIZE_SCREEN_X * SIZE_SCREEN_Y * 4];

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
	unsigned int* getVideoBuffer();

	unsigned int getCurrentFrame();
};

#endif