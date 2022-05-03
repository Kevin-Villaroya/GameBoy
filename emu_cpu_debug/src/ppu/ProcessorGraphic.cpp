#include "ProcessorGraphic.h"
#include "../util/BitMath.h"
#include "../cpu/Processor.h"
#include <iostream>
#include <unistd.h>
#define LCDS 0xFF41

ProcessorGraphic::ProcessorGraphic(Display* screen, Memory* ram) : screen(screen), ram(ram), spriteFetcher(ram), tileFetcher(&spriteFetcher){
    this->currentFrame = 0;
    this->ticks = 0;
    this->setCurrentState(ProcessorGraphicState::OAMSearch);
    
    
    for(int i=0 ; i<SIZE_SCREEN_X*SIZE_SCREEN_Y*4 ; i++){
            this->videoBuffer[i] = 0;
    }

}

void ProcessorGraphic::setCurrentState(ProcessorGraphicState state){
    unsigned char lcdsVal = this->ram->get(LCDS) & 0b11111100;
    this->currentState = state;
    switch(state){
        case(ProcessorGraphicState::OAMSearch):
            this->ram->set(LCDS, lcdsVal|0b10);
            break;
        case(ProcessorGraphicState::PixelTransfer):
            this->ram->set(LCDS, lcdsVal|0b11);
            break;
        case(ProcessorGraphicState::HBlank):
            this->ram->set(LCDS, lcdsVal|0b00);
            break;
        case(ProcessorGraphicState::VBlank):
            this->ram->set(LCDS, lcdsVal|0b01);
            break;
    }
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
    //printf("oamSearch\n");
    if(this->ticks >= 80){
        this->setCurrentState(ProcessorGraphicState::PixelTransfer);

        this->tileFetcher.reset();
    }

    if(this->ticks == 1)
        this->spriteFetcher.loadSprites();
}

void ProcessorGraphic::pixelTransfer(){
    //printf("pixelTransfer\n");

    this->tileFetcher.start(this->ram,this->ticks, this->videoBuffer);

    if(this->tileFetcher.getPixelPushed() >= SIZE_SCREEN_X){
        this->tileFetcher.clearFifo();
        this->setCurrentState(ProcessorGraphicState::HBlank);

        if(this->ram->get(Memory::LCD) & (1 << 3)){
                unsigned char interruptFlags = this->ram->get(Memory::IF);
                this->ram->set(Memory::IF, interruptFlags|IT_LCD_STAT);
        }
    }


    /*
    this->tileFetcher.tick();

    while(this->tileFetcher.hasPixel()){
        unsigned char pixelRaw = this->tileFetcher.popPixel();
        this->pixelLine[x] = pixelRaw;
        this->x++;
    }
    

    if(this->x == 160){        
        this->spriteFetcher.fetch(this->pixelLine);

        while(this->spriteFetcher.hasPixel()){
            unsigned char pixelRaw = this->spriteFetcher.popPixel();
            unsigned char pixel = (this->ram->get(Memory::BGP) >> ((uint8_t)pixelRaw * 2)) & 3;

            this->screen->write(pixel);
        }

        this->screen->HBlank();
        this->currentState = ProcessorGraphicState::HBlank;
    }
    */
}

void ProcessorGraphic::hBlank(){
    //printf("hBlank\n");
    if(this->ticks >= MAX_LINE_TICKS){
        this->incrementLy();
        unsigned char ly = this->ram->get(Memory::LY);

        if(ly >= SIZE_SCREEN_Y){
            this->setCurrentState(ProcessorGraphicState::VBlank);
            unsigned char interruptFlags = this->ram->get(Memory::IF);
            this->ram->set(Memory::IF, interruptFlags|IT_VBLANK);

            if(this->ram->get(Memory::LCD) & (1 << 4)){
                unsigned char interruptFlags = this->ram->get(Memory::IF);
                this->ram->set(Memory::IF, interruptFlags|IT_LCD_STAT);
            }

            this->currentFrame++;

            //if(currentFrame == 9) sleep(100);

        }
        else{
            this->setCurrentState(ProcessorGraphicState::OAMSearch);
        }
        this->ticks = 0;

    }

    /*
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
    */
}

void ProcessorGraphic::incrementLy(){
    unsigned char lcds = this->ram->get(Memory::LCD);
    unsigned char ly = this->ram->get(Memory::LY);
    unsigned char lyc = this->ram->get(Memory::LYC);
    
    ly++;
    this->ram->set(Memory::LY, ly);
    
    if(ly == lyc){
        lcds |= 0b100;
        this->ram->set(Memory::LCD, lcds);
        if(lcds & (1 << 6)){
            unsigned char interruptFlags = this->ram->get(Memory::IF);
            this->ram->set(Memory::IF, interruptFlags|IT_LCD_STAT);
        }
    }
    else{
        lcds &= 0b11111011;
        this->ram->set(Memory::LCD, lcds);
    }
}


void ProcessorGraphic::vBlank(){
    //printf("vblank\n");
    if(this->ticks >= MAX_LINE_TICKS){
        this->incrementLy();
        
        if(this->ram->get(Memory::LY) >= MAX_FRAME_LINE){
            this->setCurrentState(ProcessorGraphicState::OAMSearch);
            this->ram->set(Memory::LY, 0);
        }
        this->ticks = 0;

    }

    /*
    this->ram->requestInterupt(0); //set interruption vblank
    if(this->ticks == 1){
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
    */
}

unsigned int* ProcessorGraphic::getVideoBuffer(){
    return this->videoBuffer;
}


unsigned int ProcessorGraphic::getCurrentFrame(){
    return this->currentFrame;
}



ProcessorGraphic::~ProcessorGraphic(){}