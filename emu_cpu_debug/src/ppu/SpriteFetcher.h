#ifndef __SPRITE_FETCHER_H__
#define __SPRITE_FETCHER_H__

#include <queue>
#include "../memory/Memory.h"

class SpriteFetcher{
    private:
        Memory* ram;
        unsigned char *pixelLine;
        unsigned int size;
    public:
        void start(Memory* ram);
        void fetch(unsigned char *pixelLine);

        bool hasPixel();
        unsigned char popPixel();
};

#endif