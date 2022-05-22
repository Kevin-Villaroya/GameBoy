#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include <vector>  
#include "Display.h"
#include "../memory/Memory.h"

class Window : public Display{
    private:
        const int INIT_SIZE_X_WINDOW = 160;
        const int INIT_SIZE_Y_WINDOW = 144;

        SDL_Color palette[4];
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Surface *screen;

        SDL_Window* debugWindow;
        SDL_Renderer* debugRenderer;
        SDL_Texture* debugTexture;
        SDL_Surface*  debugScreen;

        uint8_t* bufferTexture;
        unsigned int offset;

        void initPalette();
        void setColorAt(unsigned int pos, uint8_t color);

        uint64_t time;

        Memory* memory;

        void updateDebuger();
        void debugerDisplay(SDL_Surface *surface, uint16_t startLocation, uint16_t tileNum, int x, int y);

        void uiKey(bool down, SDL_Keycode);
    public:
        Window(Memory*);
        void update(unsigned int* videoBuffer)override;
        void write(unsigned char color) override;
        void HBlank() override;
        void VBlank() override;
        Event fetchEvent() override;

        ~Window();
};

#endif