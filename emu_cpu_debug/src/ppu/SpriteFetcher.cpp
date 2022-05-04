#include "SpriteFetcher.h"
#include "TileFetcher.h"
#include "../util/BitMath.h"
#include <iostream>

SpriteFetcher::SpriteFetcher(Memory* r):ram(r){
}

void SpriteFetcher::start(Memory* ram){
    this->ram = ram;
}

void SpriteFetcher::loadSprites(){  
    while(!currentSpritesOnLine.empty())
        currentSpritesOnLine.pop_front();
    for(int i=0 ; i<10 ; i++){
        while(!spriteList[i].empty())
            spriteList[i].pop_front();
    }
    
    unsigned char ly = ram->get(Memory::LY);
    unsigned char height = ram->get(Memory::LCDC) & 0b100 ? 16 : 8;

    for(int i=0 ; i< 40 ; i++){
        Oam oam;
        oam.yPos = this->ram->get(0xFE00 + (i*4) + 0);
        oam.xPos = this->ram->get(0xFE00 + (i*4) + 1);
        oam.tileIndex = this->ram->get(0xFE00 + (i*4) + 2);
        oam.flags = this->ram->get(0xFE00 + (i*4) + 3);
        if(!oam.xPos)
            continue;

        if(this->currentSpritesOnLine.size() >= 10)
            break;
        
        if(oam.yPos <= ly + 16 && oam.yPos + height > ly + 16){ 
            //spriteList[currentSpritesOnLine.size()].push_back(oam);

            if (this->currentSpritesOnLine.empty()) {
                this->currentSpritesOnLine.push_front(oam);
                continue;
            }
            unsigned int i = 0;
            for(; i<this->currentSpritesOnLine.size() ; i++){
                if(this->currentSpritesOnLine.front().xPos > oam.xPos){
                    break;
                }
                this->currentSpritesOnLine.push_back(this->currentSpritesOnLine.front());
                this->currentSpritesOnLine.pop_front();
            }
            this->currentSpritesOnLine.push_front(oam);
            
            for(unsigned int j=0 ; j<i ; j++){
                this->currentSpritesOnLine.push_front(this->currentSpritesOnLine.back());
                this->currentSpritesOnLine.pop_back();   
            }
        }
    }
    //printf("load sprites: %i\n", this->currentSpritesOnLine.size());
    
}




unsigned int SpriteFetcher::fetch(TileFetcher* tf, int bitPos, unsigned int color, unsigned char bgColor){
    for(int i=0 ; i<this->oamEntriesCounter ; i++){
        int spriteX = (this->oamEntries[i].xPos - 8) + ((this->ram->get(Memory::SCX) % 8));
        
        if(spriteX + 8 < tf->getXptr())
            continue;
    
        
        int offSet = tf->getXptr() - spriteX;

        if((offSet < 0) || (offSet > 7))
            continue;

        bitPos = (7 - offSet);

        if(this->oamEntries[i].flags & 0b100000 )//x flip
            bitPos = offSet;


        unsigned char* fetchOamData = tf->getFetchOamData();   

        unsigned char hi = !!(fetchOamData[i * 2] & (1 << bitPos));
        unsigned char lo = !!(fetchOamData[(i * 2) + 1] & (1 << bitPos)) << 1;

        if(!(hi|lo))
            continue;
        

        if(!(this->oamEntries[i].flags & 0b10000000) || bgColor == 0){ //prioryti background
            color = (this->oamEntries[i].flags & 0b10000) ? this->ram->getSp2Color(hi|lo) : this->ram->getSp1Color(hi|lo);
            if(hi|lo)
                break;
            
        }
    }

    return color;



    /*
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
    */
}

void SpriteFetcher::loadSpriteTile(TileFetcher* tf){    
    std::queue<Oam> copy;
    for(unsigned int i=0 ; i<this->currentSpritesOnLine.size() ; i++)
        copy.push(this->currentSpritesOnLine.at(i));

    while(!copy.empty()){
        int xSprite = (copy.front().xPos - 8) + (this->ram->get(Memory::SCX));

        if(((xSprite >= tf->getXfetch() && xSprite < tf->getXfetch() + 8) || ((xSprite + 8) >= tf->getXfetch() && (xSprite + 8) < tf->getXfetch() + 8))){
            this->oamEntries[this->oamEntriesCounter++] = copy.front();
        }
        copy.pop();
        if(copy.empty() || this->oamEntriesCounter >= 3){
            break;
        }
    }
}

void SpriteFetcher::loadSpriteData(TileFetcher* tf, int offSet){
    int ly = this->ram->get(Memory::LY);
    unsigned char height = this->ram->get(Memory::LCDC) & 0b100 ? 16 : 8;

    for(int i=0 ; i<this->oamEntriesCounter ; i++){
        unsigned char tileY = ((ly + 16) - this->oamEntries[i].yPos) * 2;

        if (this->oamEntries[i].flags & 0b100000) {//flip y
            tileY = ((height * 2) - 2) - tileY;
        }

        unsigned char tileIndex = this->oamEntries[i].tileIndex;

        if (height == 16) {
            tileIndex &= ~(1); 
        }

        tf->getFetchOamData()[(i * 2) + offSet] = 
            this->ram->get(0x8000 + (tileIndex * 16) + tileY + offSet);
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

void SpriteFetcher::setOamEntriesCounter(int v){
    this->oamEntriesCounter = v;
}

int SpriteFetcher::spritesOnLine(){
    return this->currentSpritesOnLine.size();
}