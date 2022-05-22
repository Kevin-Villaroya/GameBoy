#include <iostream>
#include "Window.h"
#include "../gamepad/Gamepad.h"
#include "SDL2/SDL_ttf.h"


Window::Window(Memory *m){
    this->memory = m;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1024, 768 , 0, &this->window, &this->renderer);
    this->screen = SDL_CreateRGBSurface(0, 1024, 768, 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);
    this->texture = SDL_CreateTexture(this->renderer,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                1024, 768);

    SDL_CreateWindowAndRenderer(16*8*4, 32*8*4, 0, &this->debugWindow, &this->debugRenderer);
    this->debugScreen = SDL_CreateRGBSurface(0,(16 * 8 * 4) + (16 * 4), 
                                            (32 * 8 * 4) + (64 * 4), 32,
                                            0x00FF0000,
                                            0x0000FF00,
                                            0x000000FF,
                                            0xFF000000);
    this->debugTexture = SDL_CreateTexture(this->debugRenderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            (16 * 8 * 4) + (16 * 4), 
                                            (32 * 8 * 4) + (64 * 4));

    int x, y;
    SDL_GetWindowPosition(this->window, &x, &y);
    SDL_SetWindowPosition(this->debugWindow, x + INIT_SIZE_X_WINDOW*4 + 10, y);

}

void Window::update(unsigned int* videoBuffer){
    SDL_Rect rc;
    rc.x = rc.y = 0;
    rc.w = rc.h = 2048;
    for (int line_num = 0; line_num < INIT_SIZE_Y_WINDOW; line_num++) {
        for (int x = 0; x < INIT_SIZE_X_WINDOW; x++) {
            rc.x = x * 4;
            rc.y = line_num * 4;
            rc.w = 4;
            rc.h = 4;
            
            SDL_FillRect(this->screen, &rc, videoBuffer[x + (line_num * INIT_SIZE_X_WINDOW)]);
        }
    }

    SDL_UpdateTexture(this->texture, NULL, this->screen->pixels, this->screen->pitch);
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);

    updateDebuger();
}

void Window::debugerDisplay(SDL_Surface *surface, uint16_t startLocation, uint16_t tileNum, int x, int y){
    unsigned long tile_colors[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000};
    SDL_Rect rect;

    for (int tileY=0; tileY<16; tileY += 2) {
        uint8_t b1 = this->memory->get((startLocation + (tileNum * 16) + tileY));
        uint8_t b2 = this->memory->get(startLocation + (tileNum * 16) + tileY + 1);

        for (int bit=7; bit >= 0; bit--) {
            uint8_t hi = !!(b1 & (1 << bit)) << 1;
            uint8_t lo = !!(b2 & (1 << bit));

            uint8_t color = hi | lo;

            rect.x = x + ((7 - bit) * 4);    
            rect.y = y + (tileY / 2 * 4);
            rect.w = 4;
            rect.h = 4;

            SDL_FillRect(surface, &rect, tile_colors[color]);
        }
    }
}

void Window::updateDebuger(){
    int xDraw = 0;
    int yDraw = 0;
    int tileNum = 0;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = this->debugScreen->w;
    rect.h = this->debugScreen->h;
    SDL_FillRect(this->debugScreen, &rect, 0xFF111111);

    uint16_t addr = 0x8000;

    //384 tiles, 24 x 16
    for (int y=0; y<24; y++) {
        for (int x=0; x<16; x++) {
            debugerDisplay(this->debugScreen, addr, tileNum, xDraw + (x * 4), yDraw + (y * 4));
            xDraw += (8 * 4);
            tileNum++;
        }

        yDraw += (8 * 4);
        xDraw = 0;
    }

	SDL_UpdateTexture(this->debugTexture, NULL, debugScreen->pixels, debugScreen->pitch);
	SDL_RenderClear(this->debugRenderer);
	SDL_RenderCopy(this->debugRenderer, this->debugTexture, NULL, NULL);
	SDL_RenderPresent(this->debugRenderer);
}



void Window::HBlank(){

}

void Window::VBlank(){
    this->offset = 0;

    SDL_UpdateTexture(this->texture, NULL, this->bufferTexture, INIT_SIZE_X_WINDOW * 4);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void Window::uiKey(bool down, SDL_Keycode key){
    if(key == SDLK_UP){
        Gamepad::getInstance()->getState()->up = down;
    }

    if(key == SDLK_DOWN){
        Gamepad::getInstance()->getState()->down = down;
    }

    if(key == SDLK_LEFT){
        Gamepad::getInstance()->getState()->left = down;
    }

    if(key == SDLK_RIGHT){
        Gamepad::getInstance()->getState()->right = down;
    }

    if(key == SDLK_a){
        Gamepad::getInstance()->getState()->a = down;
    }

    if(key == SDLK_s){
        Gamepad::getInstance()->getState()->b = down;
    }

    if(key == SDLK_RETURN){
        Gamepad::getInstance()->getState()->start = down;
    }

    if(key == SDLK_TAB){
        Gamepad::getInstance()->getState()->select = down;
    }
}

Event Window::fetchEvent(){
    SDL_Event events;            

    while(SDL_PollEvent(&events) > 0){
        if((events.type == SDL_WINDOWEVENT) && (events.window.event == SDL_WINDOWEVENT_CLOSE)){
            return Event::QUIT;
        }

        switch(events.type){
            case SDL_QUIT:
                return Event::QUIT;
                break;
            case SDL_KEYUP:
                this->uiKey(false, events.key.keysym.sym);
                break;
            case SDL_KEYDOWN:
                this->uiKey(true, events.key.keysym.sym);
                break;
            default:
                return Event::NONE;
                break;
        }
        
    }
    
    return Event::NONE;
}

void Window::initPalette(){
    this->palette[0] = {0xe0, 0xf0, 0xe7, 0xff}; // White
    this->palette[1] = {0x8b, 0xa3, 0x94, 0xff}; // Light Gray
    this->palette[2] = {0x55, 0x64, 0x5a, 0xff}; // Dark Gray
    this->palette[3] = {0x34, 0x3d, 0x37, 0xff}; // Black
}

void Window::setColorAt(unsigned int pos, uint8_t color){
    if(pos >= 0 && pos < INIT_SIZE_X_WINDOW * INIT_SIZE_Y_WINDOW * 4 * sizeof(uint8_t)){
        this->bufferTexture[pos] = color;    
    }
}

Window::~Window(){
    delete this->bufferTexture;

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyTexture(this->texture);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
void Window::write(unsigned char color){}