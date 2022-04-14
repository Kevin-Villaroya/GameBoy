#include "TileFetcher.h"
#include "../util/BitMath.h"
#include <iostream>

void TileFetcher::tick(){
    this->pixel++;

    this->ticks++;
    if(this->ticks == 2){
        this->ticks = 0;

        switch (this->currentState){
            case PixelFetcherState::ReadTileId:
                if(this->hasToRenderTiles){
                    this->readTileId();
                }
                break;
        
            case PixelFetcherState::ReadTileData0:
                if(this->hasToRenderTiles){
                    this->readTileData0();
                }
                break;

            case PixelFetcherState::ReadTileData1:
                if(this->hasToRenderTiles){
                    this->readTileData1();
                }
                break;

            case PixelFetcherState::PushToFIFO:
                this->pushToFIFO();
                break;

            default:
                break;
        }
    }
}

void TileFetcher::start(Memory* ram){
    this->ram = ram;
    this->pixel = 0;
    this->ticks = 0;
    this->tileData = 0;
    this->backgroundMemory = 0;
    this->unsignedValue = true;
    this->usingWindow = false;

    this->hasToRenderTiles = testBit(this->ram->get(Memory::LCDC), 0);

    this->scrollX = this->ram->get(Memory::SCX);
    this->scrollY = this->ram->get(Memory::SCY);
    this->windowX = this->ram->get(Memory::WX);
    this->windowY = this->ram->get(Memory::WY);

    if(testBit(this->ram->get(Memory::LCDC), 5)){
        if(this->windowY <= this->ram->get(Memory::LY)){
            this->usingWindow = true;
        }
    }

    if(testBit(this->ram->get(Memory::LCDC), 4)){
        this->tileData = 0x8000;
    }else{
        tileData = 0x8800;
        this->unsignedValue = false;
    }

    if(!this->usingWindow){
        if(testBit(this->ram->get(Memory::LCDC), 3)){
            this->backgroundMemory = 0x9C00;
        }else{
            this->backgroundMemory = 0x9800;
        }
    }

    if(!usingWindow){
        this->yPos = this->scrollY + this->ram->get(Memory::LY);
    }else{
        this->yPos = this->ram->get(Memory::LY) - this->windowY;
    }

    this->tileRow = ((unsigned char)(this->yPos / 8)) * 32;

    this->currentState = PixelFetcherState::ReadTileId;

    this->line = yPos % 8;
    this->line *= 2;

    
    while(this->fifo.size() > 0){
        this->fifo.pop();
    }
}

void TileFetcher::readTileId(){
    unsigned short xPos = this->pixel + this->scrollX;

    if(this->usingWindow){
        if(this->pixel >= this->windowX){
            xPos = this->pixel - this->windowX;
        }
    }

    unsigned short tileColumn = xPos / 8;
    signed short tileNumber;

    unsigned short tileAddress = this->backgroundMemory + this->tileRow + tileColumn;

    if(this->unsignedValue){
        tileNumber = (unsigned char)this->ram->get(tileAddress);
    }else{
        tileNumber = (signed char)this->ram->get(tileAddress);
    }

    this->tileLocation = this->tileData;

    if(this->unsignedValue){
        this->tileLocation += tileNumber * 16;
    }else{
        this->tileLocation += (tileNumber + 128) * 16;
    }
    
    this->currentState = PixelFetcherState::ReadTileData0;
}

void TileFetcher::readTileData0(){
    unsigned char data = this->ram->get(tileLocation + line);

    for(size_t bitPos = 0; bitPos < 8; bitPos++){
        this->pixelData[bitPos] = (data >> bitPos) & 0b00000001;
    }

    this->currentState = PixelFetcherState::ReadTileData1;
}

void TileFetcher::readTileData1(){
    unsigned char data = this->ram->get(tileLocation + line + 1);

    for(size_t bitPos = 0; bitPos < 8; bitPos++){
        unsigned char value = (data >> bitPos) & 0b00000001;

        if(value == 1){
            this->pixelData[bitPos] |= ((data >> bitPos) & 0b00000001) << 1;
        }
    }


    this->currentState = PixelFetcherState::PushToFIFO;
}

void TileFetcher::pushToFIFO(){
    if(this->fifo.size() <= 8){
        for(int i = 7; i >= 0; i--){
            this->fifo.push(this->pixelData[i]);
        }

        this->currentState = PixelFetcherState::ReadTileId;
    }
}

bool TileFetcher::hasPixel(){
    return !this->fifo.empty();
}

unsigned char TileFetcher::popPixel(){
    unsigned char value = this->fifo.front();
    this->fifo.pop();

    return value;
}