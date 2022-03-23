#include "Terminal.h"
#include <iostream>

Terminal::Terminal(){
    this->palette[0] = "█";
    this->palette[1] = "▒";
    this->palette[2] = "░";
    this->palette[3] = " ";
}

void Terminal::write(unsigned char color){
    std::cout <<this->palette[color]<<this->palette[color];
}

void Terminal::HBlank(){
    std::cout << std::endl;
}

void Terminal::VBlank(){
    //std::cout<< "\033[2J";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}