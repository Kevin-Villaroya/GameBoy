#include "TileFetcher.h"
#include "../util/BitMath.h"
#include "../util/DecToHex.h"
#include "../memory/Memory.h"
#include <iostream>

TileFetcher::TileFetcher(SpriteFetcher* sp):spriteFetcher(sp){
    this->currentState = PixelFetcherState::ReadTileId;
    this->pixelPushed = 0;
    this->xLine = 0;
    this->clearFifo();
}

void TileFetcher::tick(){
    switch (this->currentState){
        case PixelFetcherState::ReadTileId:
            this->readTileId();
            break;
    
        case PixelFetcherState::ReadTileData0:
            this->readTileData0();
            break;

        case PixelFetcherState::ReadTileData1:
            this->readTileData1();
            break;
        
        case PixelFetcherState::Idle:
            //printf("Idle\n");
            this->currentState = PixelFetcherState::PushToFIFO;
            break;

        case PixelFetcherState::PushToFIFO:
            this->pushToFIFO();    
            break;

        default:
            break;
    }
}

void TileFetcher::reset(){
    this->currentState = PixelFetcherState::ReadTileId;
    this->pixelPushed = 0;
    this->xLine = 0;
    this->xFetch = 0;
    this->xPtr = 0;
}

void TileFetcher::clearFifo(){
    while(!this->fifo.empty())
        this->fifo.pop();
}

void TileFetcher::start(Memory* ram, unsigned int ppuLineTicks, unsigned int* videoBuffer){
    this->ram = ram;
    this->yMap = (ram->get(Memory::LY) + ram->get(Memory::SCY));
    this->xMap = (this->xFetch + ram->get(Memory::SCX));
    this->yTile = ((ram->get(Memory::LY) + ram->get(Memory::SCY)) % 8) * 2;
    /*printf("tileFetch yMap: %02X xMap: %02X yTile: %02X\n", 
        this->yMap, 
        this->xMap, 
        this->yTile);
    */


    if(!(ppuLineTicks & 1)){
        this->tick();
    }
    
    this->pushPixel(videoBuffer);

#include "TileFetcher.h"
}

void TileFetcher::pushPixel(unsigned int* videoBuffer){
    if (this->fifo.size() > 8) {
        unsigned int pixelData = this->fifo.front();
        unsigned int p = pixelData;
        this->fifo.pop();

        if (this->xLine >= (ram->get(Memory::SCX) % 8)) {
            videoBuffer[this->pixelPushed + ((this->ram->get(Memory::LY) * 160))] = pixelData;
            ////printf("%08X\n", pixelData);

            this->pixelPushed++;
        }

        this->xLine++;
    }
    //printf("push pixel fifoSize: %i pixelData: %08X pixelPushed:%02X xLine:%02X\n", this->fifo.size(), p, this->pixelPushed, this->xLine);
}

void TileFetcher::readTileId(){
    this->spriteFetcher->setOamEntriesCounter(0);
    if (this->ram->get(Memory::LCDC) & 0b1) {
        this->bgwData[0] = this->ram->get(
            ((this->ram->get(Memory::LCDC) & 0b1000) ? 0x9C00 : 0x9800) + 
            (this->xMap / 8) + 
            (((this->yMap / 8)) * 32));

        if (( (this->ram->get(Memory::LCDC)&0b10000) ? 0x8000 : 0x8800) == 0x8800) {
            this->bgwData[0] += 128;
        }
    }

    if((this->ram->get(Memory::LCDC) & 0b10) && this->spriteFetcher->spritesOnLine()){
        //printf("%i\n",this->spriteFetcher->spritesOnLine() );
        this->spriteFetcher->loadSpriteTile(this);
    }
    

    this->currentState = PixelFetcherState::ReadTileData0;
    this->xFetch += 8;
    //printf("readTile bgw_fetch[0]: %02X fetchX: %02X\n", this->bgwData[0], this->xFetch);
}

void TileFetcher::readTileData0(){
    this->bgwData[1] = this->ram->get(
        ((this->ram->get(Memory::LCDC)&0b10000) ? 0x8000 : 0x8800) +
        (this->bgwData[0] * 16) + 
        this->yTile);

    this->spriteFetcher->loadSpriteData(this, 0);    
    this->currentState = PixelFetcherState::ReadTileData1;
    //printf("readTileData0 bgw_fectch[1]: %02X\n", this->bgwData[1]);
}

void TileFetcher::readTileData1(){
    this->bgwData[2] = this->ram->get(
        ((this->ram->get(Memory::LCDC)&0b10000) ? 0x8000 : 0x8800) +
        (this->bgwData[0] * 16) + 
        this->yTile + 1);

    this->spriteFetcher->loadSpriteData(this, 1);    
    this->currentState = PixelFetcherState::Idle;
    //printf("readTileData0 bgw_fectch[2]: %02X\n", this->bgwData[2]);
}

void TileFetcher::pushToFIFO(){
    //printf("pushToFIFIO\n");
    if(this->fifo.size() > 8){
        //printf("fifo full\n");
        return;
    }
    int x = this->xFetch - (8 - (this->ram->get(Memory::SCX) % 8));

    for (int i=0; i<8; i++) {
        int bit = 7 - i;
        unsigned char hi = !!(this->bgwData[1] & (1 << bit));
        unsigned char lo = !!(this->bgwData[2] & (1 << bit)) << 1;
        
        unsigned int color = this->ram->getBgpColor(hi | lo);

        if(!(this->ram->get(Memory::LCDC) & 0b1)){
            color = this->ram->getBgpColor(0);
        }

        if(this->ram->get(Memory::LCDC) & 0b10){
            color = this->spriteFetcher->fetch(this, bit, color, hi|lo);
            //printf("%08X\n", color);
        }

        if (x >= 0) {
            this->fifo.push(color);
            this->xPtr++;
            //printf("color pushed: %08X\n", color);
        }
    }   

    this->currentState = PixelFetcherState::ReadTileId;
}

int TileFetcher::getPixelPushed(){
    return this->pixelPushed;
}

unsigned char TileFetcher::getXptr(){
    return this->xPtr;
}

unsigned char* TileFetcher::getFetchOamData(){
    return this->fetchOamData;
}

unsigned char TileFetcher::getXfetch(){
    return this->xFetch;
}