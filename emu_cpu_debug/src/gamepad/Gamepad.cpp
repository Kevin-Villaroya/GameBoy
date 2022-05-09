#include "Gamepad.h"
#include "../util/DecToHex.h"
#include <iostream>

Gamepad* Gamepad::instance = nullptr;

Gamepad::Gamepad(){
    this->state = {0};
    this->buttonSelected = false;
    this->directionSelected = false;
}

Gamepad* Gamepad::getInstance(){
    if(Gamepad::instance == nullptr){
        Gamepad::instance = new Gamepad();
    }

    return Gamepad::instance;
}

bool Gamepad::isButtonSelected(){
    return this->buttonSelected;
}

bool Gamepad::isDirectionSelected(){
    return this->directionSelected;
}

void Gamepad::set(unsigned char value){
    this->buttonSelected = value & 0x20;
    this->directionSelected = value & 0x10;
}

unsigned char Gamepad::get(){
    unsigned char output = 0xCF;

    if(!this->isButtonSelected()){
        if(this->state.start){
            output &= ~(1 << 3);
        }else if(this->state.select){
            output &= ~(1 << 2);
        }else if(this->state.a){
            output &= ~(1 << 0);
        }else if(this->state.b){
            output &= ~(1 << 1);
        }
    }

    if(!this->isDirectionSelected()){
        if(this->state.left){
            output &= ~(1 << 1);
        }else if(this->state.right){
            output &= ~(1 << 0);
        }else if(this->state.up){
            output &= ~(1 << 2);
        }else if(this->state.down){
            output &= ~(1 << 3);
        }
    }

    return output;
}

State* Gamepad::getState(){
    return &this->state;
}