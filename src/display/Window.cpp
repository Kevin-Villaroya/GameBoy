#include <iostream>
#include "Window.h"

Window::Window(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        throw "Error"; 
    }

    this->window = SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INIT_SIZE_X_WINDOW * 2, INIT_SIZE_Y_WINDOW * 2, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, INIT_SIZE_X_WINDOW, INIT_SIZE_Y_WINDOW);

    this->initPalette();
    this->offset = 0;
    this->time = 0;

    this->bufferTexture = (uint8_t*)malloc(INIT_SIZE_X_WINDOW * INIT_SIZE_Y_WINDOW * 4 * sizeof(uint8_t));
}

void Window::write(unsigned char color){
    SDL_Color paletteColor = this->palette[color];

    this->setColorAt(this->offset + 0, paletteColor.r);
    this->setColorAt(this->offset + 1, paletteColor.g);
    this->setColorAt(this->offset + 2, paletteColor.b);
    this->setColorAt(this->offset + 3, paletteColor.a);

    this->offset += 4;
}

void Window::HBlank(){

}

void Window::VBlank(){
    this->offset = 0;

    SDL_UpdateTexture(this->texture, NULL, this->bufferTexture, INIT_SIZE_X_WINDOW * 4);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

Event Window::fetchEvent(){
    SDL_Event events;

    bool findEvent = false;

    while(SDL_PollEvent(&events)){
        if(!findEvent){
            findEvent = true;
            switch(events.type){
                case SDL_QUIT:
                    return Event::QUIT;
                    break;
                case SDL_KEYUP:
                    if(events.key.keysym.sym == SDLK_i){
                        return Event::SKIP;
                    }else if(events.key.keysym.sym == SDLK_t){
                        return Event::TICK;
                    }else if(events.key.keysym.sym == SDLK_b){
                        return Event::WAIT_OPCODE_BREAKER;
                    }else if(events.key.keysym.sym == SDLK_d){
                        return Event::DUMP_RAM;
                    }else if(events.key.keysym.sym == SDLK_g){
                        return Event::CONTINUE;
                    }else if(events.key.keysym.sym == SDLK_a){
                        return Event::A;
                    }else if(events.key.keysym.sym == SDLK_s){
                        return Event::S;
                    }else if(events.key.keysym.sym == SDLK_RETURN){
                        return Event::RETURN;
                    }else if(events.key.keysym.sym == SDLK_SPACE){
                        return Event::SPACE;
                    }else if(events.key.keysym.sym == SDLK_RIGHT){
                        return Event::RIGHT;
                    }else if(events.key.keysym.sym == SDLK_LEFT){
                        return Event::LEFT;
                    }else if(events.key.keysym.sym == SDLK_UP){
                        return Event::UP;
                    }else if(events.key.keysym.sym == SDLK_DOWN){
                        return Event::DOWN;
                    }
                default:
                    return Event::NONE;
                    break;
            }
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