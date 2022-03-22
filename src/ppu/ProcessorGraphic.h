#ifndef __PPU_H__
#define __PPU_H__

class ProcessorGraphic{
private:
	void oamSearch();
	void pixelTransfer();
	void HBlank();
	void VBlank();
public:
	void tick();
};

#endif