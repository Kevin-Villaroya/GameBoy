#include "ProcessorGraphic.h"
#include <iostream>

ProcessorGraphic::ProcessorGraphic(){
    this->x = 0;
    this->ticks = 0;
    this->screen = new Terminal();
    this->currentState = ProcessorGraphicState::OAMSearch;
}

void ProcessorGraphic::tick(Memory& ram){
    this->ticks++;

    switch (this->currentState){
        case ProcessorGraphicState::OAMSearch:
            this->oamSearch(ram);
            
            break;

        case ProcessorGraphicState::PixelTransfer:
            this->pixelTransfer(ram);
            break;

        case ProcessorGraphicState::HBlank:
            this->hBlank(ram);
            break;

        case ProcessorGraphicState::VBlank:
            this->vBlank(ram);
            break;

        default:
            break;
    }
}

void ProcessorGraphic::oamSearch(Memory& ram){
    if(this->ticks == 40){
        this->x = 0;
        unsigned char tileLine = this->getLY(ram) % 8;
        unsigned short tileMapRowAddr = 0x9800 + ((this->getLY(ram) / 8) * 32);

        this->fetcher.start(tileMapRowAddr, tileLine);
        this->currentState = ProcessorGraphicState::PixelTransfer;
    }
}

void ProcessorGraphic::pixelTransfer(Memory& ram){
    this->fetcher.tick(ram);

    if(this->fetcher.hasPixel()){
        this->screen->write(this->fetcher.popPixel());
        this->x++;
    }

    if(this->x == 160){
        //std::cout << "go HBlank" << std::endl;
        this->screen->HBlank();
        this->currentState = ProcessorGraphicState::HBlank;
    }
}

void ProcessorGraphic::hBlank(Memory& ram){
     if(this->ticks == 456){
        this->ticks = 0;
        this->setLY(ram, this->getLY(ram) + 1);

        if(this->getLY(ram) == 144){
            std::cout << "go VBlank" << std::endl;
            this->screen->VBlank();
            this->currentState = ProcessorGraphicState::VBlank;
        }else{
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::vBlank(Memory& ram){
    if(this->ticks == 456){
        this->ticks = 0;
        this->setLY(ram, this->getLY(ram) + 1);

        if(this->getLY(ram) == 153){
            this->setLY(ram, 0);
            //std::cout << "go OAMSearch" << std::endl;
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

unsigned char ProcessorGraphic::getLY(Memory& ram){
    return ram[0xff44];
}

void ProcessorGraphic::setLY(Memory& ram, unsigned char value){
    ram.set(0xFF44, value);
}

ProcessorGraphic::~ProcessorGraphic(){
    delete this->screen;
}