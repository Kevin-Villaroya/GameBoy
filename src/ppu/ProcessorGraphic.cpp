#include "ProcessorGraphic.h"
#include <iostream>

ProcessorGraphic::ProcessorGraphic(Display* screen, Memory* ram) : screen(screen), ram(ram){
    this->x = 0;
    this->ticks = 0;
    this->currentState = ProcessorGraphicState::OAMSearch;
}

void ProcessorGraphic::tick(){
    this->ticks++;

    switch (this->currentState){
        case ProcessorGraphicState::OAMSearch:
            this->oamSearch();
            
            break;

        case ProcessorGraphicState::PixelTransfer:
            this->pixelTransfer();
            break;

        case ProcessorGraphicState::HBlank:
            this->hBlank();
            break;

        case ProcessorGraphicState::VBlank:
            this->vBlank();
            break;

        default:
            break;
    }
}

void ProcessorGraphic::oamSearch(){
    if(this->ticks == 40){
        this->x = 0;
        unsigned short y = this->ram->get(Memory::LY) + this->ram->get(Memory::SCY);

        unsigned char tileLine = y % 8;
        unsigned short tileMapRowAddr = 0x9800 + ((y / 8) * 32);

        this->fetcher.start(tileMapRowAddr, tileLine);
        this->currentState = ProcessorGraphicState::PixelTransfer;
    }
}

void ProcessorGraphic::pixelTransfer(){
    this->fetcher.tick(*this->ram);

    if(this->fetcher.hasPixel()){
        unsigned char pixelRaw = this->fetcher.popPixel();
        unsigned char pixel = (this->ram->get(Memory::BGP) >> ((uint8_t)pixelRaw * 2)) & 3;

        this->screen->write(pixel);
        this->x++;
    }

    if(this->x == 160){
        this->screen->HBlank();
        this->currentState = ProcessorGraphicState::HBlank;
    }
}

void ProcessorGraphic::hBlank(){
     if(this->ticks == 456){
        this->ticks = 0;
        this->ram->set(Memory::LY, this->ram->get(Memory::LY) + 1);

        if(this->ram->get(Memory::LY) == 144){
            this->screen->VBlank();
            this->currentState = ProcessorGraphicState::VBlank;
        }else{
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::vBlank(){
    if(this->ticks == 0){
        this->ram->requestInterupt(0); //set interruption vblank
    }
    
    if(this->ticks == 456){
        this->ticks = 0;
       this->ram->set(Memory::LY, this->ram->get(Memory::LY) + 1);

        if(this->ram->get(Memory::LY) == 153){
            this->ram->set(Memory::LY, 0);
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

ProcessorGraphic::~ProcessorGraphic(){}