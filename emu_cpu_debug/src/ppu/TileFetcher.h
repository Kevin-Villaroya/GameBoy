#ifndef __PIXEL_FETCHER_H__
#define __PIXEL_FETCHER_H__

#include <queue>
#include "../memory/Memory.h"

enum class PixelFetcherState{
    ReadTileId,
    ReadTileData0,
    ReadTileData1,
    Idle,
    PushToFIFO
};

class TileFetcher{
private:
    std::queue<unsigned int> fifo;
    PixelFetcherState currentState;

    Memory* ram;

    unsigned char pixelPushed;
    unsigned char xLine;
    unsigned char xFetch;
    unsigned char bgwData[3];
    unsigned char fetchOamData[6];
    unsigned char yMap;
    unsigned char xMap;
    unsigned char yTile;
    unsigned char xFifo;
    

    void readTileId();
    void readTileData0();
    void readTileData1();
    void pushToFIFO();
    void pushPixel(unsigned int* videoBuffer);
    
public:
    TileFetcher();
    void tick();
    void start(Memory* ram, unsigned int ppuLineTicks, unsigned int* videoBuffer);
    
    bool hasPixel();
    unsigned char popPixel();

    void reset();
    void clearFifo();

    int getPixelPushed();

};

#endif