#ifndef __PPU_H__
#define __PPU_H__

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

	ProcessorGraphicState currentState;

	// Number of lines displayed
	unsigned int LY;

	// Tick associated to the current line being drawed
	unsigned int ticks;

	// Number of pixels displayed in the current line
	unsigned int x;

	// tick passed in the state VBlank
	unsigned int VBlankTick;

	void drawLine();
	void collectSprite();
public:
	ProcessorGraphic();

	void tick();
};

#endif