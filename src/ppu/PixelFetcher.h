#ifndef __PIXEL_FETCHER_H__
#define __PIXEL_FETCHER_H__

#include <queue>
#include "../memory/Memory.h"

enum class PixelFetcherState{
    ReadTileId,
    ReadTileData0,
    ReadTileData1,
    PushToFIFO
};

class PixelFetcher{
private:
    std::queue<unsigned char> fifo;
    unsigned int ticks;
    PixelFetcherState currentState;

    unsigned short tileIndex;
    unsigned short mapAddr;
    unsigned char tileLine;
    unsigned char tileId;

    unsigned char pixelData[8];

    void readTileId(Memory& ram);
    void readTileData0(Memory& ram);
    void readTileData1(Memory& ram);
    void pushToFIFO();
public:
    void tick(Memory& ram);
    void start(unsigned short tileMapRowAddr, unsigned char tileLine);

    bool hasPixel();
    unsigned char popPixel();
};

#endif