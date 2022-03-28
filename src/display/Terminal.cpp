#include "Terminal.h"
#include <iostream>
#include <SDL2/SDL.h>

Terminal::Terminal(){
    this->palette[0] = "█";
    this->palette[1] = "▒";
    this->palette[2] = "░";
    this->palette[3] = " ";

    this->time = 0;
}

void Terminal::write(unsigned char color){
    std::cout <<this->palette[color]<<this->palette[color];
}

void Terminal::HBlank(){
    std::cout << std::endl;
}

void Terminal::VBlank(){
    std::cout << SDL_GetPerformanceCounter() - this->time << std::endl;
    this->time = SDL_GetPerformanceCounter();
    std::cout<< "\033[2J";
}

Event Terminal::fetchEvent(){
    return Event::NONE;
}