#include "SpriteFetcher.h"
#include "../util/BitMath.h"
#include <iostream>

void SpriteFetcher::start(Memory* ram){
    this->ram = ram;
}

void SpriteFetcher::fetch(unsigned char *pixelLine){
    this->pixelLine = pixelLine;
    this->size = 160;

    bool use8x16 = false;
    if(testBit(this->ram->get(Memory::LCDC), 2)){
        use8x16 = true;
    }

    int scanline = this->ram->get(Memory::LY);

    for(int sprite = 0; sprite < 40; sprite++){
        unsigned char index = sprite * 4;
        unsigned char yPos = this->ram->get(0xFE00 + index) - 16;
        unsigned char xPos = this->ram->get(0xFE00 + index + 1) - 8;
        unsigned char tileLocation = this->ram->get(0xFE00 + index + 2);
        unsigned char attributes = this->ram->get(0xFE00 + index + 3);

        bool yFlip = testBit(attributes, 6);
        bool xFlip = testBit(attributes, 5);

        int ySize = 8;
        if(use8x16){
            ySize = 16;
        }

        //if in this scanline we have to draw the sprite
        if(scanline >= yPos && scanline < (yPos + ySize)){
            int line = scanline - yPos;

            //read in reverse
            if(yFlip){
                line -= ySize;
                line *= -1;
            }

            line *= 2;

            unsigned short dataAddress = (0x8000 + (tileLocation * 16)) + line;

            unsigned char data1 = this->ram->get(dataAddress);
            unsigned char data2 = this->ram->get(dataAddress + 1);

            for(int tilePixel = 7; tilePixel >= 0; tilePixel--){
                int colourBit = tilePixel;

                if(xFlip){
                    colourBit -= 7;
                    colourBit *= -1;
                }

                int xPix = 0 - tilePixel;
                xPix += 7;

                int pixel = xPos+xPix;

                int colourNum = bitGetVal(data2, colourBit);
                colourNum <<= 1;
                colourNum |= bitGetVal(data1, colourBit);

                this->pixelLine[pixel] = colourNum;
            }
        }
    }
}

bool SpriteFetcher::hasPixel(){
    return this->size > 0;
}

unsigned char SpriteFetcher::popPixel(){
    unsigned char value = pixelLine[160 - size];
    this->size--;

    return value;
}