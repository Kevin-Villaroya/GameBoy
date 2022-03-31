#ifndef __REGISTER_PROCESSOR_GRAPHIC_H__
#define __REGISTER_PROCESSOR_GRAPHIC_H__

#include "../memory/Memory.h"

class RegisterProcessorGraphic{
	private:
		Memory* ram;

		unsigned char LY; //CURRENT HORIZONTAL LINE
		unsigned char LCDC; //
		unsigned char BGP; //BACKGROUND PALETTE
		unsigned char SCY; //BACKGROUND SCROLL Y
		unsigned char SCX; //BACKGROUND SCROLL X
		unsigned char WY; //WINDOW SCROLL Y
		unsigned char WX; //WINDOW SCROLL X
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

		unsigned char getSCX();
		void setSCX(unsigned char value);	

		unsigned char getWY();
		void setWY(unsigned char value);

		unsigned char getWX();
		void setWX(unsigned char value);
};

#endif