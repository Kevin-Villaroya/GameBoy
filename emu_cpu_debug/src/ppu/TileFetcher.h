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

class TileFetcher{
private:
    std::queue<unsigned char> fifo;
    PixelFetcherState currentState;

    Memory* ram;

    bool hasToRenderTiles;

    unsigned char ticks;

    unsigned char pixel;
    unsigned char yPos;
    unsigned short tileData;
    unsigned short tileLocation;
    unsigned short tileRow;
    unsigned char line;
    unsigned short backgroundMemory;
    bool unsignedValue;
    bool usingWindow;

    unsigned char scrollX;
    unsigned char scrollY;
    unsigned char windowX;
    unsigned char windowY;

    unsigned char pixelData[8];

    void setFifoOfBlanks();

    void readTileId();
    void readTileData0();
    void readTileData1();
    void pushToFIFO();
public:
    void tick();
    void start(Memory* ram);

    bool hasPixel();
    unsigned char popPixel();
};

#endif