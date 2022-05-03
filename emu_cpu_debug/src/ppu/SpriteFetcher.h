#ifndef __SPRITE_FETCHER_H__
#define __SPRITE_FETCHER_H__

#include <deque>
#include "../memory/Memory.h"
#include "TileFetcher.h"
struct Oam{
    unsigned char yPos;
    unsigned char xPos;
    unsigned char tileIndex;
    unsigned char flags;
};

class SpriteFetcher{
    private:
        Memory* ram;
        unsigned char *pixelLine;
        unsigned int size;
        Oam oamEntries[3];//oam_fetched_entry
        int oamEntriesCounter;//fectched_entry_count
        std::deque<Oam> currentSpritesOnLine;//line_sprites
        std::deque<Oam> spriteList[10];//line_entry_array
    public:
        SpriteFetcher(Memory *ram);
        void start(Memory* ram);
        unsigned int fetch(TileFetcher*, int bitPos, unsigned int color, unsigned char bgColor);
        void loadSprites();
        void loadSpriteTile(TileFetcher*);
        void loadSpriteData(TileFetcher*, int offSet);

        bool hasPixel();
        unsigned char popPixel();
        void setOamEntriesCounter(int);
        

        int spritesOnLine();
};

#endif