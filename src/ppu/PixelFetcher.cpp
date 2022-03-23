#include "PixelFetcher.h"
#include <iostream>

void PixelFetcher::tick(Memory& ram){
    this->ticks++;
    if(this->ticks == 2){
        this->ticks = 0;

        switch (this->currentState){
            case PixelFetcherState::ReadTileId:
                this->readTileId(ram);
                break;
        
            case PixelFetcherState::ReadTileData0:
                this->readTileData0(ram);
                break;

            case PixelFetcherState::ReadTileData1:
                this->readTileData1(ram);
                break;

            case PixelFetcherState::PushToFIFO:
                this->pushToFIFO();
                break;

            default:
                break;
        }
    }
}

void PixelFetcher::start(unsigned short tileMapRowAddr, unsigned char tileLine){
    this->tileIndex = 0;
    this->mapAddr = tileMapRowAddr;
    this->tileLine = tileLine;
    this->ticks = 0;

    this->currentState = PixelFetcherState::ReadTileId;

    while(this->fifo.size() > 0){
        this->fifo.pop();
    }
}

void PixelFetcher::readTileId(Memory& ram){
    this->tileId = ram.get(this->mapAddr + ((unsigned short)this->tileIndex));

    this->currentState = PixelFetcherState::ReadTileData0;
}

void PixelFetcher::readTileData0(Memory& ram){
    unsigned short offset = 0x8000 + ((unsigned short)this->tileId) * 16;

    unsigned short addr = offset + ((unsigned short)this->tileLine) * 2;

    unsigned char data = ram.get(addr);

    for(size_t bitPos = 0; bitPos < 8; bitPos++){
        this->pixelData[bitPos] = (data >> bitPos) & 0b00000001;
    }

    this->currentState = PixelFetcherState::ReadTileData1;
}

void PixelFetcher::readTileData1(Memory& ram){
    unsigned short offset = 0x8000 + ((unsigned short)this->tileId) * 16;

    unsigned short addr = offset + ((unsigned short)this->tileLine) * 2;

    unsigned char data = ram.get(addr + 1);

    for(size_t bitPos = 0; bitPos < 8; bitPos++){
        unsigned char value = (data >> bitPos) & 0b00000001;

        if(value == 1){
            this->pixelData[bitPos] |= ((data >> bitPos) & 0b00000001) << 1;
        }
    }

    this->currentState = PixelFetcherState::PushToFIFO;
}

void PixelFetcher::pushToFIFO(){
    if(this->fifo.size() <= 8){
        for(int i = 7; i >= 0; i--){
            this->fifo.push(this->pixelData[i]);
        }

        this->tileIndex++;
        this->currentState = PixelFetcherState::ReadTileId;
    }
}

bool PixelFetcher::hasPixel(){
    return !this->fifo.empty();
}

unsigned char PixelFetcher::popPixel(){
    unsigned char value = this->fifo.front();
    this->fifo.pop();

    return value;
}