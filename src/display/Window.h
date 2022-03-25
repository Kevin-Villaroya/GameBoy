#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>  
#include "Display.h"

class Window : public Display{
    private:
        const int INIT_POS_X_WINDOW = 0;
        const int INIT_POS_Y_WINDOW = 0;
        const int INIT_SIZE_X_WINDOW = 160;
        const int INIT_SIZE_Y_WINDOW = 144;

        SDL_Color palette[4];
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Window();

        void write(unsigned char color) override;
        void HBlank() override;
        void VBlank() override;
        Event fetchEvent();

        ~Window();
};

#endif