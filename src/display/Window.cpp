#include "Window.h"

Window::Window(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        throw "Error"; 
    }

    this->window = SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INIT_SIZE_X_WINDOW, INIT_SIZE_Y_WINDOW, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

void Window::write(unsigned char color){

}

void Window::HBlank(){

}

void Window::VBlank(){

}

Event Window::fetchEvent(){
    SDL_Event events;

    while (SDL_PollEvent(&events)){
        switch (events.type){
            case SDL_QUIT:
                return Event::QUIT;
            default:
                return Event::NONE;
        }
    }

    return Event::NONE;
}

Window::~Window(){
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}