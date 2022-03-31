#ifndef __REGISTER_PROCESSOR_GRAPHIC_H__
#define __REGISTER_PROCESSOR_GRAPHIC_H__

#include "../memory/Memory.h"

class RegisterProcessorGraphic{
	private:
		Memory* ram;

		unsigned char LY;
		unsigned char LCDC;
		unsigned char BGP;
		unsigned char SCY;
	public:
		RegisterProcessorGraphic(Memory* ram);	

		unsigned char getLY();
		void setLY(unsigned char value);

		unsigned char getLCDC();
		void setLCDC(unsigned char value);

		unsigned char getBGP();
		void setBGP(unsigned char value);

		unsigned char getSCY();
		void setSCY(unsigned char value);	
};

#endif