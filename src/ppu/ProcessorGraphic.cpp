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
        unsigned char tileLine = this->getLY() % 8;
        unsigned short tileMapRowAddr = 0x9800 + ((this->getLY() / 8) * 32);

        this->fetcher.start(tileMapRowAddr, tileLine);
        this->currentState = ProcessorGraphicState::PixelTransfer;
    }
}

void ProcessorGraphic::pixelTransfer(){
    this->fetcher.tick(*this->ram);

    if(this->fetcher.hasPixel()){
        unsigned char pixelRaw = this->fetcher.popPixel();
        unsigned char pixel = (this->getBGP() >> ((uint8_t)pixelRaw * 2)) & 3;

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
        this->setLY(this->getLY() + 1);

        if(this->getLY() == 144){
            this->screen->VBlank();
            this->currentState = ProcessorGraphicState::VBlank;
        }else{
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::vBlank(){
    if(this->ticks == 456){
        this->ticks = 0;
        this->setLY(this->getLY() + 1);

        if(this->getLY() == 153){
            this->setLY(0);
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

unsigned char ProcessorGraphic::getLY(){
    return ram->get(0xff44);
}

void ProcessorGraphic::setLY(unsigned char value){
    ram->set(0xFF44, value);
}

unsigned char ProcessorGraphic::getLCDC(){
    return ram->get(0xff40);
}

void ProcessorGraphic::setLCDC(unsigned char value){
    ram->set(0xff40, value);
}

unsigned char ProcessorGraphic::getBGP(){
    return ram->get(0xff47);
}

void ProcessorGraphic::setBGP(unsigned char value){
    ram->set(0xff47, value);
}

ProcessorGraphic::~ProcessorGraphic(){}