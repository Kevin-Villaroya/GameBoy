#include "ProcessorGraphic.h"

ProcessorGraphic::ProcessorGraphic(){
    this->x = 0;
    this->ticks = 0;
    this->LY = 0; //TODO maybe take this value in the memory
    this->screen = new Terminal();
}

void ProcessorGraphic::tick(Memory& ram){
    this->ticks++;

    switch (this->currentState){
        case ProcessorGraphicState::OAMSearch:
            this->oamSearch();
            
            break;

        case ProcessorGraphicState::PixelTransfer:
            this->pixelTransfer(ram);
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
    this->x = 0;
    unsigned char tileLine = this->LY % 8;
    unsigned short tileMapRowAddr = 0x9800 + ((this->LY / 8) * 32);

    this->fetcher.start(tileMapRowAddr, tileLine);

    if(this->ticks == 40){
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
        this->screen->HBlank();
        this->currentState = ProcessorGraphicState::HBlank;
    }
}

void ProcessorGraphic::hBlank(){
     if(this->ticks == 456){
        this->ticks = 0;
        this->LY++;

        if(this->LY == 144){
            this->screen->VBlank();
            this->currentState = ProcessorGraphicState::VBlank;
        }else{
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::vBlank(){
    if(this->ticks >= 10){
        if(this->ticks == 456){
            this->ticks = 0;
            this->LY++;

            if(this->LY == 153){
                this->LY = 0;
                this->currentState = ProcessorGraphicState::OAMSearch;
            }
        }
    }
}

ProcessorGraphic::~ProcessorGraphic(){
    delete this->screen;
}